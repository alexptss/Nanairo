/*!
  \file spectra_setting_node.cpp
  \author Sho Ikeda

  Copyright (c) 2015-2017 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#include "spectra_setting_node.hpp"
// Standard C++ library
#include <array>
#include <cstddef>
#include <istream>
#include <memory>
#include <ostream>
#include <tuple>
#include <vector>
// Zisc
#include "zisc/binary_data.hpp"
#include "zisc/utility.hpp"
// Nanairo
#include "setting_node_base.hpp"
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/Color/spectral_distribution.hpp"

namespace nanairo {

/*!
  */
void RgbParameters::readData(std::istream* data_stream) noexcept
{
  zisc::read(&rgb_[0], data_stream, sizeof(rgb_[0]) * 3);
}

/*!
  */
void RgbParameters::writeData(std::ostream* data_stream) const noexcept
{
  zisc::write(&rgb_[0], data_stream, sizeof(rgb_[0]) * 3);
}

/*!
  */
SpectraParameters::SpectraParameters() noexcept
{
  spectra_.reserve(2);
  spectra_.emplace_back(zisc::cast<double>(CoreConfig::shortestWavelength()), 0.0);
  spectra_.emplace_back(zisc::cast<double>(CoreConfig::longestWavelength()), 0.0);
}

/*!
  */
void SpectraParameters::readData(std::istream* data_stream) noexcept
{
  uint32 spectra_size = 0;
  zisc::read(&spectra_size, data_stream);
  if (0 < spectra_size) {
    spectra_.resize(zisc::cast<std::size_t>(spectra_size));
    zisc::read(&spectra_[0], data_stream, sizeof(spectra_[0]) * spectra_.size());
  }
}

/*!
  */
void SpectraParameters::writeData(std::ostream* data_stream) const noexcept
{
  const uint32 spectra_size = zisc::cast<uint32>(spectra_.size());
  zisc::write(&spectra_size, data_stream);
  if (0 < spectra_size)
    zisc::write(&spectra_[0], data_stream, sizeof(spectra_[0]) * spectra_.size());
}

/*!
  */
ColorRepresentationType SpectraSettingNode::representationType() const noexcept
{
  return color_type_;
}

/*!
  */
void SpectraSettingNode::initialize() noexcept
{
  setRepresentationType(ColorRepresentationType::kRgb);
}

/*!
  */
void SpectraSettingNode::readData(std::istream* data_stream) noexcept
{
  {
    zisc::read(&color_type_, data_stream);
    setRepresentationType(color_type_);
  }
  if (parameters_)
    parameters_->readData(data_stream);
}

/*!
  */
RgbParameters& SpectraSettingNode::rgbParameters() noexcept
{
  ZISC_ASSERT(representationType() == ColorRepresentationType::kRgb,
              "Invalid color type is specified.");
  auto parameters = zisc::cast<RgbParameters*>(parameters_.get());
  return *parameters;
}

/*!
  */
const RgbParameters& SpectraSettingNode::rgbParameters() const noexcept
{
  ZISC_ASSERT(representationType() == ColorRepresentationType::kRgb,
              "Invalid color type is specified.");
  auto parameters = zisc::cast<const RgbParameters*>(parameters_.get());
  return *parameters;
}

/*!
  */
void SpectraSettingNode::setRepresentationType(const ColorRepresentationType type) noexcept
{
  color_type_ = type;
  // Initialize parameters
  parameters_.reset();
  switch (color_type_) {
   case ColorRepresentationType::kRgb: {
    parameters_ = std::make_unique<RgbParameters>();
    break;
   }
   case ColorRepresentationType::kSpectra: {
    parameters_ = std::make_unique<SpectraParameters>();
    break;
   }
   default:
    break;
  }
}

/*!
  */
SpectraParameters& SpectraSettingNode::spectraParameters() noexcept
{
  ZISC_ASSERT(representationType() == ColorRepresentationType::kSpectra,
              "Invalid color type is specified.");
  auto parameters = zisc::cast<SpectraParameters*>(parameters_.get());
  return *parameters;
}

/*!
  */
const SpectraParameters& SpectraSettingNode::spectraParameters() const noexcept
{
  ZISC_ASSERT(representationType() == ColorRepresentationType::kSpectra,
              "Invalid color type is specified.");
  auto parameters = zisc::cast<SpectraParameters*>(parameters_.get());
  return *parameters;
}

/*!
  */
SettingNodeType SpectraSettingNode::type() const noexcept
{
  return SettingNodeType::kSpectra;
}

/*!
  */
void SpectraSettingNode::writeData(std::ostream* data_stream) const noexcept
{
  writeType(data_stream);
  zisc::write(&color_type_, data_stream);
  if (parameters_)
    parameters_->writeData(data_stream);
}

} // namespace nanairo
