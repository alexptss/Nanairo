/*!
  \file sensor.cpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#include "sensor.hpp"
// Standard C++ library
#include <tuple>
#include <utility>
// Zisc
#include "zisc/error.hpp"
// Nanairo
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/CameraModel/camera_model.hpp"
#include "NanairoCore/Material/shader_model.hpp"
#include "NanairoCore/Sampling/sampled_direction.hpp"
#include "NanairoCore/Sampling/sampled_point.hpp"
#include "NanairoCore/Sampling/sampled_spectra.hpp"


namespace nanairo {

/*!
  \details
  No detailed.
  */
Sensor::Sensor(const CameraModel* camera,
               const uint x,
               const uint y) noexcept :
    camera_{camera},
    x_{x},
    y_{y}
{
  initialize(x, y);
}

/*!
  \details
  No detailed.
  */
Float Sensor::evalPdf(
    const Vector3* /* vin */,
    const Vector3* vout,
    const Vector3& /* normal */,
    const WavelengthSamples& /* wavelengths */) const noexcept
{
  ZISC_ASSERT(vout != nullptr, "The vout is NULL.");
  const Float pdf = camera().calcPdf(*vout);
  return pdf;
}

/*!
  \details
  No detailed.
  */
SampledSpectra Sensor::evalRadiance(
    const Vector3* /* vin */,
    const Vector3* vout,
    const Vector3& /* normal */,
    const WavelengthSamples& wavelengths) const noexcept
{
  ZISC_ASSERT(vout != nullptr, "The vout is NULL.");
  const Float f = camera().calcRadiance(*vout);
  return SampledSpectra{wavelengths, f};
}

/*!
  \details
  No detailed.
  */
std::tuple<SampledSpectra, Float> Sensor::evalRadianceAndPdf(
    const Vector3* /* vin */,
    const Vector3* vout,
    const Vector3& /* normal */,
    const WavelengthSamples& wavelengths) const noexcept
{
  ZISC_ASSERT(vout != nullptr, "The vout is NULL.");
  const auto result = camera().calcRadianceAndPdf(*vout);
  const Float f = std::get<0>(result);
  const Float pdf = std::get<1>(result);
  return std::make_tuple(SampledSpectra{wavelengths, f}, pdf);
}

/*!
  \details
  No detailed.
  */
std::tuple<SampledDirection, SampledSpectra> Sensor::sample(
    const Vector3* /* vin */,
    const Vector3& /* normal */,
    const WavelengthSamples& wavelengths,
    Sampler& /* sampler */) const noexcept
{
  const auto vout = camera().sampleDirection(x_, y_);
  const auto weight = SampledSpectra{wavelengths, 1.0};
  return std::make_tuple(vout, weight);
}

/*!
  \details
  No detailed.
  */
bool Sensor::wavelengthIsSelected() const noexcept
{
  return false;
}

/*!
  \details
  No detailed.
  */
inline
const CameraModel& Sensor::camera() const noexcept
{
  return *camera_;
}

/*!
  \details
  No detailed.
  */
void Sensor::initialize(const uint /* x */, const uint /* y */) noexcept
{
}

} // namespace nanairo
