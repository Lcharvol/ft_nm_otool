
#/bin/sh

param=$1

ret=$(ls | grep RET)
if [ -f $ret ]
then
	rm -rf RET
fi

nb=$(ls $1 | wc -l);
file=($(ls $1));


# echo $file
# echo $nb
rm -rf file
mkdir file
make

for i in `seq 0 $nb`;
do
	if [ -f $1/${file[$i]} ]
	then
		echo "Test On $1/${file[$i]}"
		path=file/${file[$i]}
		mkdir $path
		nm $1/${file[$i]} &> $path/nm
 		./ft_nm $1/${file[$i]} &> $path/ft_nm
		diff -u $path/nm $path/ft_nm &> $path/diff_nm
		result=$(cat $path/diff_nm | wc -l)
		if [ $result != "0" ]
		then
			echo "\033[31;1mdiff for $path/nm \033[0m";
		else
			rm -rf $path/ft_nm $path/diff_nm $path/nm
		fi
		otool -t $1/${file[$i]} &> $path/otool
 		./ft_otool $1/${file[$i]} &> $path/ft_otool
		diff -u $path/otool $path/ft_otool &> $path/diff_otool
		result=$(cat $path/diff_otool | wc -l)
		if [ $result != "0" ]
		then
			echo "\033[31;1mdiff for $path/otool \033[0m";
		else
			rm -rf $path/ft_otool $path/diff_otool $path/otool
		fi
	fi
done