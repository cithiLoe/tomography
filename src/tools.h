#pragma once

#include <set>
#include <vector>

#include "distribution.h"
#include "grid.h"
#include "ray.h"
#include "reconstruction.h"
#include "vector_sparse.h"

using SparseMatrix = std::vector<VectorSparse>;
using SleMatrix = std::vector<std::vector<Ray>>;

// Forming task SLE
void data_to_sle(const SleMatrix &data, SparseMatrix &phi, std::vector<double> &integrals, const Grid &test);
void data_to_sle(const SleMatrix &data, SparseMatrix &phi, const Grid &test);

// Calculating residual
double compute_residual(const Grid &x, const SparseMatrix &A, const std::vector<double> &m);
std::vector<double> compute_vector_residual(const Grid &x, const SparseMatrix &A, const std::vector<double> &m);

// Reading data from specified path
SleMatrix get_data(const std::string &path, const unsigned startTime = 0, const unsigned finishTime = 24);

// Station coordinates
std::set<std::pair<double, double>> get_stations(const SleMatrix& data);

void solve_sle(Grid &grid, const SparseMatrix &matrix, const std::vector<double> &integrals, const double error, const Solver &solver, const bool onlyPositive = true);

double degree_to_radian(const double degree);
double radian_to_degree(const double radian);

std::vector<unsigned> create_intervals(const unsigned first, const unsigned last);
