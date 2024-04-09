#include <pybind11/pybind11.h>
#include "Main.h"

namespace py = pybind11;

PYBIND11_MODULE(FurrywolfEngine, m)
{
  m.doc() = R"pbdoc(
        C++ binding for FurryWolfEngine
        -----------------------
        .. currentmodule:: FurrywolfEngine

        .. autosummary::
           :toctree: _generate

        start
    )pbdoc";

  m.def("RavUp", &Ravup, "Rav up the Engine!");
}
