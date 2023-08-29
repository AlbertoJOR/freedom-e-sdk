source env.sh

make BSP=metal PROGRAM=Ascon_Test TARGET=freedom-e310-arty clean
make BSP=metal PROGRAM=Ascon_Test TARGET=freedom-e310-arty software
make BSP=metal PROGRAM=Ascon_Test TARGET=freedom-e310-arty upload


