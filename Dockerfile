FROM quay.io/pypa/manylinux2014_x86_64
RUN git clone https://github.com/aromalma/geoposition-packages-cpp.git
WORKDIR geoposition-packages-cpp/
RUN for i in $(find /opt/python/ -name cp3*); do $i/bin/pip install pybind11; $i/bin/python setup.py bdist_wheel; done
WORKDIR dist/
RUN for i in $(ls ./*.whl);do auditwheel repair $i; done
WORKDIR /



