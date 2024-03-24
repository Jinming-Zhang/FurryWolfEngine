#include <pybind11/pybind11.h>
#include "Main.h"

namespace py = pybind11;

PYBIND11_MODULE(FurrywolfEngine, m)
{
  m.doc() = "C++ binding for FurryWolfEngine";
  m.def("start", &Ravup, "Rav up the Engine!");
}
