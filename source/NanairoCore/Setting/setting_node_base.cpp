/*!
  \file setting_node_base.cpp
  \author Sho Ikeda

  Copyright (c) 2015-2017 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#include "setting_node_base.hpp"
// Standard C++ library
#include <istream>
#include <ostream>
#include <string>
#include <utility>
// Zisc
#include "zisc/binary_data.hpp"
#include "zisc/error.hpp"
// Nanairo
#include "NanairoCore/nanairo_core_config.hpp"

namespace nanairo {

/*!
  */
NodeParameters::~NodeParameters() noexcept
{
}

/*!
  */
SettingNodeBase::SettingNodeBase() noexcept
{
}

/*!
  */
SettingNodeBase::~SettingNodeBase() noexcept
{
}

/*!
  */
void SettingNodeBase::log() const noexcept
{
}

/*!
  */
std::string SettingNodeBase::readString(std::istream* data_stream) const noexcept
{
  std::string text;

  uint32 text_length;
  zisc::read(&text_length, data_stream);

  text.resize(text_length);
  zisc::read(&text[0], data_stream, text_length);

  return text;
}

/*!
  */
SettingNodeType SettingNodeBase::readType(std::istream* data_stream) const noexcept
{
  SettingNodeType t;
  zisc::read(&t, data_stream);
  return t;
}

/*!
  */
void SettingNodeBase::writeString(const std::string& text,
                                  std::ostream* data_stream) const noexcept
{
  const uint32 text_length = zisc::cast<uint32>(text.size());
  zisc::write(&text_length, data_stream);
  zisc::write(text.data(), data_stream, text_length);
}

/*!
  */
void SettingNodeBase::writeType(std::ostream* data_stream) const noexcept
{
  const SettingNodeType t = type();
  zisc::write(&t, data_stream);
}

} // namespace nanairo
