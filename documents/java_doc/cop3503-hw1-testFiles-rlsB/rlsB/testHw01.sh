javac Hw01.java
[ $? -eq 0 ] || exit 1
java Hw01 badCmd.txt > badCmdST.txt
diff -w badCmdST.txt  badCmdValid.txt
java Hw01 in1.txt > in1ST.txt
diff -w in1ST.txt  in1Valid.txt
java Hw01 in5.txt > in5ST.txt
diff -w in5ST.txt  in5Valid.txt
java Hw01 in5del2.txt > in5del2ST.txt
diff -w in5del2ST.txt  in5del2Valid.txt
java Hw01 in5del1srch1.txt > in5del1srch1ST.txt
diff -w in5del1srch1ST.txt  in5del1srch1Valid.txt
java Hw01 in10.txt > in10ST.txt
diff -w in10ST.txt  in10Valid.txt
java Hw01 in100m50K.txt > in100m50KST.txt
diff -w in100m50KST.txt  in100m50KValid.txt
java Hw01 in10Km50M.txt > in10Km50MST.txt
diff -w in10Km50MST.txt  in10Km50MValid.txt
