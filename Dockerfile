FROM quay.io/pypa/manylinux2014_x86_64
RUN git clone https://github.com/aromalma/geoposition-packages-cpp.git
#WORKDIR geoposition-packages-cpp/
RUN echo 'cd geoposition-packages-cpp/' >> run.sh
RUN echo 'cd geoposition-packages-cpp/' >>run.sh
RUN echo 'for i in $(find /opt/python/ -name cp3*); do $i/bin/pip install pybind11; $i/bin/python setup.py bdist_wheel; done' > run.sh
#WORKDIR dist/
RUN echo 'cd dist/' >> run.sh
#RUN for i in $(ls ./*.whl);do auditwheel repair $i; done
RUN echo 'for i in $(ls ./*.whl);do auditwheel repair $i; done' >> run.sh




