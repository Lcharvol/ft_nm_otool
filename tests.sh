# export TEST_FILE="tests/hell/appsleepd"
export TEST_FILE1="tests/hell/32_exe_hard"

export TEST_FILE2="a.out"

./ft_nm $TEST_FILE1 > mon_otool.txt | nm $TEST_FILE1 > native_otool.txt && diff mon_otool.txt native_otool.txt