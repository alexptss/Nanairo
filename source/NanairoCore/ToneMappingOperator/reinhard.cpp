/*!
  \file reinhard.cpp
  \author Sho Ikeda

  Copyright (c) 2015-2016 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#include "reinhard.hpp"
// Nanairo
#include "tone_mapping_operator.hpp"
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/system.hpp"

namespace nanairo {

/*!
  \details
  No detailed.
  */
Reinhard::Reinhard(const System& system, const QJsonObject& settings) noexcept :
    ToneMappingOperator(system, settings)
{
}

/*!
  */
Float Reinhard::tonemap(const Float x) const noexcept
{
  return x / (1.0 + x);
}

} // namespace nanairo
