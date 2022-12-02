make clean
make all

./pgmEcho Files/Assemble4.pgm test.pgm
./pgmComp Files/Assemble4.pgm test.pgm
./pgmReduce Files/Assemble4.pgm 4 testReduced.pgm
./pgmTile Files/Assemble4.pgm 2 "samplefile_<row>_<column>.pgm"
./pgmAssemble test3.pgm 4 4 0 0 samplefile_0_0.pgm 0 1 samplefile_0_1.pgm 1 0 samplefile_1_0.pgm 1 1 samplefile_1_1.pgm

rm -r *pgm
rm -r *dSYM
rm -r *o
make clean