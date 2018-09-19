# export TEST_FILE="tests/hell/appsleepd"
export TEST_FILE1="tests/hell/32_exe_hard_corupted"

export TEST_FILE2="a.out"

./ft_otool $TEST_FILE1 > mon_otool.txt | otool -t $TEST_FILE1 > native_otool.txt && diff mon_otool.txt native_otool.txt