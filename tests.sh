# export TEST_FILE="tests/hell/appsleepd"
export TEST_FILE1="tests/special/ahah"

export TEST_FILE2="a.out"

./ft_otool $TEST_FILE1 $TEST_FILE2 > mon_otool.txt && otool -t $TEST_FILE1 $TEST_FILE2 > native_otool.txt && diff mon_otool.txt native_otool.txt