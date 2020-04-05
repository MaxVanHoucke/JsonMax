echo ______________________________
echo "BUILDING"
echo ______________________________
mkdir -p build
cd build || exit 1
cmake ..
make

echo ______________________________
echo "RUNNING TESTS"
echo ______________________________
cd test || exit 1
./JsonMaxTests

echo ______________________________
echo "GENERATING SINGLE INCLUDE"
echo ______________________________
cd ../src/include_generator || exit 1
./JsonMaxIncludeGenerator

echo ______________________________
echo "BUILDING AGAIN WITH SINGLE INCLUDE"
echo ______________________________
cd ../../
make

echo ______________________________
echo "RUNNING DEMOS"
echo ______________________________
cd examples/sweets || exit 1
# Suppress output by storing to dev null
./JsonMaxDemoSweets > /dev/null
cd ../weather || exit 1
./JsonMaxDemoWeather > /dev/null
