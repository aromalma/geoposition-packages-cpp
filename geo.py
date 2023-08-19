import geo
print(geo.geo_split("N23.4556E34.66780"))
p=geo.query(["n34.56e34.781","n34.56e34.781","12.3465,56.223","n34.56e34.781"])
print(p.nearest("12.345,56.233"))
