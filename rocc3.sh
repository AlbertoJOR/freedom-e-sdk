source env.sh

make BSP=metal PROGRAM=MyRoCC3 TARGET=freedom-e310-arty-xmem clean
make BSP=metal PROGRAM=MyRoCC3 TARGET=freedom-e310-arty-xmem software
make BSP=metal PROGRAM=MyRoCC3 TARGET=freedom-e310-arty-xmem upload

