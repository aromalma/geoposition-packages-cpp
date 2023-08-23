import geo
import time
def split(d):
    h=d.split("E")
    return float(h[0][1:]),float(h[-1])
t=time.time()

c=[geo.geo_split("N23.4556E34.66780") for x in range(100)]
print(time.time()-t)

t=time.time()

c=[ split("N23.4556E34.66780") for x in range(100)]
print(time.time()-t)


# p=geo.query(["n34.56e34.781","n34.56e34.781","12.3465,56.223","n34.56e34.781"])
# print(p.nearest("12.345,56.233"))
