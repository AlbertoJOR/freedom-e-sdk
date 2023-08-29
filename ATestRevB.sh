source env.sh

make BSP=metal PROGRAM=Ascon_TestS TARGET=sifive-hifive1-revb clean
make BSP=metal PROGRAM=Ascon_TestS TARGET=sifive-hifive1-revb software
make BSP=metal PROGRAM=Ascon_TestS TARGET=sifive-hifive1-revb upload


