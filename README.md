# geoposition-packages-cpp

## Description
These packages are fully written in c++, which can easily imported to python
It has several functions for working with geo position latlongs.
published in pypi
## Installation
pip install geopac
## Usage
>>> import geo
DISTANCE BETWEEN TWO LATLONGS
>>> geo.calculateDistance('n23.45567,34.4546','34.5664,22.55') 
1690.3387755505787
>>> geo.calculateDistance('n23.45567,34.4546','34.5664,20.55')
1827.9564404300845
SPLIT STRING TO LATLONG
>>> geo.geo_split("12.4545,w45.4564")
(12.4545, -45.4564)
>>> geo.geo_split("12.34.54.11,-34.55.21.45")
(12.581697, -33.077375)
FIND NEAREST LATLONG
>>> c=geo.query(["12.3454,45.344","n33.455,w45.22.55.12","-23.461,23.456"])
>>> c.nearest("n33.450,w45.22.55.11")
(1, 40.583333, -45.381978)
>>> c.nearest("-23.471,23.416")
(2, -23.461, 23.456)
