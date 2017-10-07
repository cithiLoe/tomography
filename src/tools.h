#pragma once

#include "vector_sparse.h"
#include "grid.h"
#include "ray.h"
#include "reconstruction.h"
#include "distribution.h"
#include <vector>
#include <list>

// Forming task SLE
void data_to_sle(const std::vector<std::vector<Ray>> &data, std::vector<VectorSparse> &phi, std::vector<double> &integrals, const Grid &test);
void data_to_sle(const std::vector<std::vector<Ray>> &data, std::vector<VectorSparse> &phi, const Grid &test);

// Calculating residual
double compute_residual(const Grid &x, const std::vector<VectorSparse> &A, const std::vector<double> &m);
std::vector<double> compute_vector_residual(const Grid &x, const std::vector<VectorSparse> &A, const std::vector<double> &m);

// Reading data from specified path
std::vector<std::vector<Ray>> get_data(const std::string &path, const unsigned startTime = 0, const unsigned finishTime = 24);

// Station coordinates
std::list<std::pair<double, double>> get_station_list(std::vector<std::vector<Ray>> data);

void solve_sle(Grid &grid, const std::vector<VectorSparse> &matrix, const std::vector<double> &integrals, const double error, const bool onlyPositive = true);
void compute_parametrs(Grid &crude, Grid &accurate, const std::vector<VectorSparse> &sleMatrix, const std::vector<double> &integrals, const bool useSecondGrid, ElectronDensityDistribution &model, Dimension latitude, Dimension longitude, Dimension time, unsigned intervals, unsigned intervalsTime, double initialResidual);

double degree_to_radian(const double degree);
double radian_to_degree(const double radian);

std::list<unsigned> create_intervals(const unsigned first, const unsigned last);
