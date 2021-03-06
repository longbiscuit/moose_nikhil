//* This file is part of the MOOSE framework
//* https://www.mooseframework.org
//*
//* All rights reserved, see COPYRIGHT for full restrictions
//* https://github.com/idaholab/moose/blob/master/COPYRIGHT
//*
//* Licensed under LGPL 2.1, please see LICENSE for details
//* https://www.gnu.org/licenses/lgpl-2.1.html

#include "EqualValueNodalConstraint.h"

template <>
InputParameters
validParams<EqualValueNodalConstraint>()
{
  InputParameters params = validParams<NodalConstraint>();
  params.addRequiredParam<unsigned int>("master", "The ID of the master node");
  params.addRequiredParam<unsigned int>("slave", "The ID of the slave node");
  params.addRequiredParam<Real>("penalty", "The penalty used for the boundary term");
  return params;
}

EqualValueNodalConstraint::EqualValueNodalConstraint(const InputParameters & parameters)
  : NodalConstraint(parameters), _penalty(getParam<Real>("penalty"))
{
  _connected_nodes.push_back(getParam<unsigned int>("slave"));
  _master_node_vector.push_back(getParam<unsigned int>("master"));
}

EqualValueNodalConstraint::~EqualValueNodalConstraint() {}

Real
EqualValueNodalConstraint::computeQpResidual(Moose::ConstraintType type)
{
  switch (type)
  {
    case Moose::Master:
      return (_u_master[_j] - _u_slave[_i]) * _penalty;

    case Moose::Slave:
      return (_u_slave[_i] - _u_master[_j]) * _penalty;
  }

  return 0.;
}

Real
EqualValueNodalConstraint::computeQpJacobian(Moose::ConstraintJacobianType type)
{
  switch (type)
  {
    case Moose::MasterMaster:
      return _penalty;

    case Moose::MasterSlave:
      return -_penalty;

    case Moose::SlaveSlave:
      return _penalty;

    case Moose::SlaveMaster:
      return -_penalty;
  }

  return 0.;
}
