<?php

    $var = 7;
    printf("var is a %s\n", gettype($var));

    $var = "cs50 rocks!";
    printf("var is a %s\n", gettype($var));

    $var = true;
    printf("var is a %s\n", gettype($var));
    
    $var = 3.50;
    printf("var is a %s\n", gettype($var));
    
    $var = ["a" => 1, "b" => 2, "c" => 3];
    printf("var is a %s\n", gettype($var));
    
    $var = fopen("dynamic.php", "r");
    printf("var is a %s\n", gettype($var));
    
    $var = NULL;
    printf("var is a %s\n", gettype($var));
    
    print("\n");
    
    print("1" + 2 . "\n");

    print("CS" + 50 . "\n");
    
    print(1 + "2" . "\n");
    
    print(90 + "9 bottles of beer on the wall" . "\n");
    
    print(10 / 7 . "\n");
    
    print(7 + true . "\n");
?>
