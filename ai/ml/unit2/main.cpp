#include <Eigen/Core>

#include <iostream>
#include <numeric>

inline double hinge_loss(double z)
{
    return z >= 1.0 ? 0.0 : 1.0 - z;
}

inline double squared_loss(double z)
{
    return (z * z) / 2;
}

double empirical_risk(const Eigen::Matrix<double, 4, 3>& feature_matrix,
                      const Eigen::Vector3d& theta,
                      const Eigen::Vector4d& labels,
                      const std::function<double(double)>& loss_func)
{
    const auto tmp = labels - feature_matrix * theta;
    double risk = std::accumulate(
        std::begin(tmp), std::end(tmp), 0.0, [&loss_func](double acc, double x) { return acc += loss_func(x); });
    return risk / tmp.size();
}

int main()
{
    Eigen::Matrix<double, 4, 3> feature_matrix{
        {1.,  0., 1. },
        {1.,  1., 1. },
        {1.,  1., -1.},
        {-1., 1., 1. }
    };
    Eigen::Vector3d theta{0, 1, 2};
    Eigen::Vector4d labels{2., 2.7, -0.7, 2.};

    std::cout << "Empirical Risk using Hinge Loss: " << empirical_risk(feature_matrix, theta, labels, hinge_loss) << '\n';
    std::cout << "Empirical Risk using Squared Loss: " << empirical_risk(feature_matrix, theta, labels, squared_loss) << '\n';

    return 0;
}
