

#include "pybind11/pybind11.h"
#include "pybind11/stl.h"

#include "ndarray/pybind11.h"
#include <tuple>

#include "kht.hpp"

namespace kht {
namespace py = pybind11;
using PyLine = py::classh<Line>;


PYBIND11_MODULE(pykht, mod) {

  PyLine cls(mod, "Line");
  cls.def(py::init<double, double>());
  cls.def_readwrite("rho", &Line::rho);
  cls.def_readwrite("theta", &Line::theta);

  mod.def("find_lines",
          [](ndarray::Array<bool, 2, 2> & binary_image, std::size_t image_width, std::size_t image_height, std::int32_t cluster_min_size, std::double_t cluster_min_deviation, std::double_t delta, std::double_t kernel_min_height, std::double_t n_sigmas, std::double_t abs_kernel_min_height) -> std::vector<Line> {
            static ListOfLines lines;
            run_kht(lines, reinterpret_cast<std::uint8_t *>(binary_image.getData()), image_width, image_height, cluster_min_size, cluster_min_deviation, delta, kernel_min_height, n_sigmas, abs_kernel_min_height);
            
            std::vector<Line> output_lines;
            output_lines.reserve(lines.size());
            for (size_t i=0;  i< lines.size(); i++){
              output_lines.push_back(lines[i]);
            }
            return output_lines;
          }

);
}
}
