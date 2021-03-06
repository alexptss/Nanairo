/*!
  \file tone_mapping_operator.cpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#include "tone_mapping_operator.hpp"
// Standard C++ library
#include <vector>
// Zisc
#include "zisc/error.hpp"
#include "zisc/math.hpp"
#include "zisc/matrix.hpp"
#include "zisc/thread_pool.hpp"
#include "zisc/utility.hpp"
// Nanairo
#include "filmic.hpp"
#include "reinhard.hpp"
#include "uncharted2_filmic.hpp"
#include "NanairoCore/system.hpp"
#include "NanairoCore/Color/color_conversion.hpp"
#include "NanairoCore/Color/color_space.hpp"
#include "NanairoCore/Color/hdr_image.hpp"
#include "NanairoCore/Color/ldr_image.hpp"
#include "NanairoCore/Color/rgba_32.hpp"
#include "NanairoCore/Color/yxy_color.hpp"
#include "NanairoCore/Geometry/transformation.hpp"
#include "NanairoCore/Setting/system_setting_node.hpp"
#include "NanairoCore/Setting/setting_node_base.hpp"
#include "NanairoCore/Utility/unique_pointer.hpp"

namespace nanairo {

/*!
  \details
  No detailed.
  */
ToneMappingOperator::ToneMappingOperator(const System& system,
                                         const SettingNodeBase* settings) noexcept
{
  initialize(system, settings);
}

/*!
  \details
  No detailed.
  */
ToneMappingOperator::~ToneMappingOperator() noexcept
{
}

/*!
  \details
  No detailed.
  */
void ToneMappingOperator::map(System& system,
                              const HdrImage& hdr_image,
                              LdrImage* ldr_image) const noexcept
{
  ZISC_ASSERT(ldr_image != nullptr, "The LDR image is null.");
  ZISC_ASSERT(hdr_image.widthResolution() == ldr_image->widthResolution(),
              "The image width is difference between HDR and LDR images.");
  ZISC_ASSERT(hdr_image.heightResolution() == ldr_image->heightResolution(),
              "The image height is difference between HDR and LDR images.");
  auto map_luminance = [this, &system, &hdr_image, ldr_image](const int thread_id)
  {
    // Set the calculation range
    const auto range = system.calcThreadRange(hdr_image.numOfPixels(), thread_id);
    const auto begin = std::get<0>(range);
    const auto end = std::get<1>(range);
    // Apply tonemap to each pixel
    for (uint index = begin; index < end; ++index) {
      auto rgba32 = Rgba32{};
      if (0.0 < hdr_image[index].y()) {
        auto xyz = hdr_image[index];
        // Tone mapping
        {
          auto yxy = ColorConversion::toYxy(xyz);
          const Float l = tonemap(exposure() * yxy.Y());
          yxy.Y() = zisc::clamp(l, 0.0, 1.0);
          xyz = ColorConversion::toXyz(yxy);
        }
        // Convert XYZ to RGB
        {
          const auto to_rgb_matrix = getXyzToRgbMatrix(system.colorSpace());
          auto rgb = ColorConversion::toRgb(xyz, to_rgb_matrix);
          rgb.clampAll(0.0, 1.0);
          rgb.correctGamma(inverseGamma());
          rgba32 = ColorConversion::toIntRgb(rgb);
        }
      }
      ldr_image->get(index) = rgba32;
    }
  };

  auto& thread_pool = system.threadPool();
  constexpr uint begin = 0;
  const uint end = thread_pool.numOfThreads();
  auto result = thread_pool.enqueueLoop(map_luminance, begin, end);
  result.get();
}

/*!
  \details
  No detailed.
  */
void ToneMappingOperator::initialize(const System& system,
                                     const SettingNodeBase* settings) noexcept
{
  const auto system_settings = castNode<SystemSettingNode>(settings);

  // Gamma
  {
    inverse_gamma_ = zisc::invert(system.gamma());
  }
  // Exposure
  {
    exposure_ = zisc::cast<Float>(system_settings->exposure());
  }
}

/*!
  \details
  No detailed.
  */
UniquePointer<ToneMappingOperator> ToneMappingOperator::makeOperator(
    const System& system,
    const SettingNodeBase* settings) noexcept
{
  const auto system_settings = castNode<SystemSettingNode>(settings);

  ToneMappingOperator* method = nullptr;
  switch (system_settings->toneMappingType()) {
   case ToneMappingType::kReinhard: {
    method = new Reinhard{system, settings};
    break;
   }
   case ToneMappingType::kFilmic: {
    method = new Filmic{system, settings};
    break;
   }
   case ToneMappingType::kUncharted2Filmic: {
    method = new Uncharted2Filmic{system, settings};
    break;
   }
   default: {
    zisc::raiseError("ToneMappingError: Unsupprted type is specified.");
   }
  }
  return UniquePointer<ToneMappingOperator>{method};
}

} // namespace nanairo
