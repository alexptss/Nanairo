/*!
  \file hdr_image-inl.hpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#ifndef NANAIRO_HDR_IMAGE_INL_HPP
#define NANAIRO_HDR_IMAGE_INL_HPP

#include "hdr_image.hpp"
// Standard C++ library
#include <vector>
// Zisc
#include "zisc/utility.hpp"
// Nanairo
#include "xyz_color.hpp"
#include "NanairoCore/nanairo_core_config.hpp"

namespace nanairo {

/*!
  \details
  No detailed.
  */
inline
XyzColor& HdrImage::operator[](const uint index) noexcept
{
  return get(index);
}

/*!
  \details
  No detailed.
  */
inline
const XyzColor& HdrImage::operator[](const uint index) const noexcept
{
  return get(index);
}

/*!
  */
inline
std::vector<XyzColor>& HdrImage::data() noexcept
{
  return buffer_;
}

/*!
  */
inline
const std::vector<XyzColor>& HdrImage::data() const noexcept
{
  return buffer_;
}

/*!
  \details
  No detailed.
  */
inline
XyzColor& HdrImage::get(const uint index) noexcept
{
  return buffer_[index];
}

/*!
  \details
  No detailed.
  */
inline
const XyzColor& HdrImage::get(const uint index) const noexcept
{
  return buffer_[index];
}

/*!
  \details
  No detailed.
  */
inline
XyzColor& HdrImage::get(const uint x, const uint y) noexcept
{
  const uint index = toIndex(x, y);
  return buffer_[index];
}

/*!
  \details
  No detailed.
  */
inline
const XyzColor& HdrImage::get(const uint x, const uint y) const noexcept
{
  const uint index = toIndex(x, y);
  return buffer_[index];
}

/*!
  \details
  No detailed.
  */
inline
uint HdrImage::heightResolution() const noexcept
{
  return height_;
}

/*!
  */
inline
std::size_t HdrImage::memorySize() const noexcept
{
  return zisc::cast<std::size_t>(sizeof(buffer_[0]) * buffer_.size());
}

/*!
  */
inline
uint HdrImage::numOfPixels() const noexcept
{
  return widthResolution() * heightResolution();
}

/*!
  */
inline
uint HdrImage::size() const noexcept
{
  return zisc::cast<uint>(buffer_.size());
}

/*!
  \details
  No detailed.
  */
inline
void HdrImage::set(const uint x, const uint y, const XyzColor& color) noexcept
{
  const uint index = toIndex(x, y);
  buffer_[index] = color;
}

/*!
  \details
  No detailed.
  */
inline
uint HdrImage::widthResolution() const noexcept
{
  return width_;
}

/*!
  */
inline
uint HdrImage::toIndex(const uint x, const uint y) const noexcept
{
  return x + y * widthResolution();
}

} // namespace nanairo

#endif // NANAIRO_HDR_IMAGE_INL_HPP
