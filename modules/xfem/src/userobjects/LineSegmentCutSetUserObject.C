/****************************************************************/
/* MOOSE - Multiphysics Object Oriented Simulation Environment  */
/*                                                              */
/*          All contents are licensed under LGPL V2.1           */
/*             See LICENSE for full restrictions                */
/****************************************************************/

#include "LineSegmentCutSetUserObject.h"

// MOOSE includes
#include "MooseError.h"

template <>
InputParameters
validParams<LineSegmentCutSetUserObject>()
{
  // Get input parameters from parent class
  InputParameters params = validParams<GeometricCut2DUserObject>();

  // Add required parameters
  params.addRequiredParam<std::vector<Real>>("cut_data",
                                             "Vector of Real values providing cut information");
  // Add optional parameters
  params.addParam<std::vector<Real>>("cut_scale", "X,Y scale factors for geometric cuts");
  params.addParam<std::vector<Real>>("cut_translate", "X,Y translations for geometric cuts");
  // Class description
  params.addClassDescription("Creates a UserObject for a line segment cut on 2D meshes for XFEM");
  // Return the parameters
  return params;
}

LineSegmentCutSetUserObject::LineSegmentCutSetUserObject(const InputParameters & parameters)
  : GeometricCut2DUserObject(parameters), _cut_data(getParam<std::vector<Real>>("cut_data"))
{
  // Set up constant parameters
  const int line_cut_data_len = 6;

  // Throw error if length of cut_data is incorrect
  if (_cut_data.size() % line_cut_data_len != 0)
    mooseError("Length of LineSegmentCutSetUserObject cut_data must be a multiple of 6.");

  unsigned int num_cuts = _cut_data.size() / line_cut_data_len;

  // Assign scale and translate parameters
  std::pair<Real, Real> scale;
  if (isParamValid("cut_scale"))
  {
    auto vec_scale = getParam<std::vector<Real>>("cut_scale");
    scale = std::make_pair(vec_scale[0], vec_scale[1]);
  }
  else
  {
    scale = std::make_pair(1.0, 1.0);
  }

  std::pair<Real, Real> trans;
  if (isParamValid("cut_translate"))
  {
    auto vec_trans = getParam<std::vector<Real>>("cut_translate");
    trans = std::make_pair(vec_trans[0], vec_trans[1]);
  }
  else
  {
    trans = std::make_pair(0.0, 0.0);
  }

  // Clear _start_times & _end_times vectors initialized from
  // time_start_cut & time_end_cut values
  _cut_time_ranges.clear();

  for (unsigned int i = 0; i < num_cuts; ++i)
  {
    Real x0 = (_cut_data[i * line_cut_data_len + 0] + trans.first) * scale.first;
    Real y0 = (_cut_data[i * line_cut_data_len + 1] + trans.second) * scale.second;
    Real x1 = (_cut_data[i * line_cut_data_len + 2] + trans.first) * scale.first;
    Real y1 = (_cut_data[i * line_cut_data_len + 3] + trans.second) * scale.second;
    _cut_line_endpoints.push_back(std::make_pair(Point(x0, y0, 0.0), Point(x1, y1, 0.0)));

    _cut_time_ranges.push_back(
        std::make_pair(_cut_data[i * line_cut_data_len + 4], _cut_data[i * line_cut_data_len + 5]));
  }
}