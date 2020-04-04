mkdir -p build
cd build
cmake ..
make

#  Run tests
cd test
./JsonMaxTests

#  Check if demos with single include JsonMax.h work
cd ../examples/sweets
./JsonMaxDemoSweets > /dev/null
cd ../weather
./JsonMaxDemoWeather > /dev/null
