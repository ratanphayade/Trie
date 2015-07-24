<?php
    error_reporting(-1);
    ini_set('display_errors', 'On');

    include 'TrieTree.php';
    $root = new TrieTree();
    //Can send single words or multiple words separated by , or <space> as argument
    $root->addWords('Ratan');
    $root->addWords('Rat');
    $root->addWords('Pavan, Sanjeevini');
    //Can send single words or multiple words separated by , or <space> as argument
    echo $root->hasWords('Rat,Rata')." Words Present<br/>";
    // pass value -1 to print all the words present or else pass the charecter limit
    print_r($root->printWords(-1));
    echo $root->deleteWords('Rat'). "Words Deleted</br>";
    print_r($root->printWords(-1));
    
?>