#!/bin/bash

make bin > /dev/null
TEST_DIR=/tmp/$RANDOM.tst 
touch $TEST_DIR

trap cleanup 0 

cleanup(){
    rm $TEST_DIR
}

echo "TEST #1 (nominal situation)"
(echo -ne "hello\n"; sleep 0.05; sleep 0.05; echo -ne "world\n") | ./bin 2>&1 | cat > $TEST_DIR
diff $TEST_DIR ./data/ref > /dev/null
if [ $? -ne 0 ]
then
    echo "TEST FAIL"
    cat $TEST_DIR
    exit 1
else
    echo "TEST OK"
fi

echo ""
echo "TEST #2 (all in one call)"
TEST_DIR=/tmp/$RANDOM.tst 
(echo -ne "hello\nworld\n") | ./bin 2>&1 | cat > $TEST_DIR
diff $TEST_DIR ./data/ref > /dev/null
if [ $? -ne 0 ]
then
    echo "TEST FAIL"
    cat $TEST_DIR
    exit 1
else
    echo "TEST OK"
fi

echo ""
echo "TEST #3 (randomly split #1)"
TEST_DIR=/tmp/$RANDOM.tst 
(echo -ne "hel"; sleep 0.05; echo -ne "lo\nworld\n") | ./bin 2>&1 | cat > $TEST_DIR
diff $TEST_DIR ./data/ref > /dev/null
if [ $? -ne 0 ]
then
    echo "TEST FAIL"
    cat $TEST_DIR
    exit 1
else
    echo "TEST OK"
fi

echo ""
echo "TEST #4 (randomly split #2)"
TEST_DIR=/tmp/$RANDOM.tst 
(echo -ne "hel"; sleep 0.05; echo -ne "lo\nwor"; sleep 0.05; echo -ne "ld\n") | ./bin 2>&1 | cat > $TEST_DIR
diff $TEST_DIR ./data/ref > /dev/null
if [ $? -ne 0 ]
then
    echo "TEST FAIL"
    cat $TEST_DIR
    exit 1
else
    echo "TEST OK"
fi
