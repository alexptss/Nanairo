/*!
  \file rendering_method_setting_node.hpp
  \author Sho Ikeda

  Copyright (c) 2015-2017 Sho Ikeda
  This software is released under the MIT License.
  http://opensource.org/licenses/mit-license.php
  */

#ifndef RENDERING_METHOD_SETTING_NODE_HPP
#define RENDERING_METHOD_SETTING_NODE_HPP

// Standard C++ library
#include <istream>
#include <memory>
#include <ostream>
// Nanairo
#include "setting_node_base.hpp"
#include "NanairoCore/nanairo_core_config.hpp"
#include "NanairoCore/RenderingMethod/rendering_method.hpp"
#include "NanairoCore/Sampling/russian_roulette.hpp"

namespace nanairo {

//! \addtogroup Core
//! \{

// PathTracing has no parameter

// LightTracing has no parameter

//! ProbabilisticPPM parameters
struct ProbabilisticPpmParameters : public NodeParameters
{
  //! Read the parameters from the stream
  void readData(std::istream* data_stream) noexcept override;

  //! Write the parameters to the stream
  void writeData(std::ostream* data_stream) const noexcept override;

  double photon_search_radius_ = 0.02;
  double radius_reduction_rate_ = 2.0 / 3.0;
  uint32 num_of_photons_ = 131072;
  uint32 k_nearest_neighbor_ = 8;
};

/*!
  */
class RenderingMethodSettingNode : public SettingNodeBase
{
 public:
  //! Initialize a rendering method
  virtual void initialize() noexcept override;

  //! Print scene data
  virtual void log() const noexcept override;

  //! Return the ProbabilisticPPM parameters
  ProbabilisticPpmParameters& probabilisticPpmParameters() noexcept;

  //! Return the ProbabilisticPPM parameters
  const ProbabilisticPpmParameters& probabilisticPpmParameters() const noexcept;

  //! Return the ray cast epsilon
  double rayCastEpsilon() const noexcept;

  //! Read the setting data from the stream
  virtual void readData(std::istream* data_stream) noexcept override;

  //! Return the roulette path length
  uint32 roulettePathLength() const noexcept;

  //! Return the russian roulette type
  RouletteType rouletteType() const noexcept;

  //! Return the rendering method type
  RenderingMethodType methodType() const noexcept;

  //! Set the rendering method type
  void setMethodType(const RenderingMethodType method_type) noexcept;

  //! Set the roulette path length
  void setRoulettePathLength(const uint32 path_length) noexcept;

  //! Set the russian roulette type
  void setRouletteType(const RouletteType roulette_type) noexcept;

  //! Set the ray cast epsilon
  void setRayCastEpsilon(const double ray_cast_epsilon) noexcept;

  //! Return the setting node type
  virtual SettingNodeType type() const noexcept override;

  //! Write the setting data to the stream
  virtual void writeData(std::ostream* data_stream) const noexcept override;

 private:
  std::unique_ptr<NodeParameters> parameters_;
  RenderingMethodType method_type_;
  double ray_cast_epsilon_;
  RouletteType roulette_type_;
  uint32 roulette_path_length_;
};

//! \} Core

} // namespace nanairo

#endif // RENDERING_METHOD_SETTING_NODE_HPP
