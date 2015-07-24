<?php

require_once 'Node.php';
/*
 * @Author: Ratan Phayade
 * Class Name : TrieTree
 * This Class provides the features controls to TrieTree
 */
class TrieTree{
    /*
     * Default constructor 
     * This will create a Empty node which will be assigned to root.
     */
	function __construct(){
		$this->root = new Node('');
	}
    /*
     * method: addWords
     * Accepts a string which can contain multiple words separeted by 
     * comma(,) or space. All the words are added to the trie tree.
     */
	function addWords($string){
                $words = preg_split("/[\s,]+/", $string);
                foreach($words as $word){
                    $word = trim($word);
                    if(!empty($word)){
                        $this->root->addWord($word, 0, strlen($word));
                    }
                }
	}
    /*
     * method: hasWords
     * Accepts a string which can contain multiple words separeted by 
     * comma(,) or space. This will return the number of words actually present 
     * in the tree from given argument.
     */
	function hasWords($string){
            $count = 0;
            $words = preg_split("/[\s,]+/", $string);
            foreach($words as $word){   
                $word = trim($word);
                if(!empty($word)){
                    $count += $this->root->hasWord($word, 0, strlen($word)-1);
                }
            }          
            return $count;
	}
    /*
     * methid: deleteWords
     * Accepts a string which can contain multiple words separeted by 
     * comma(,) or space. This will return the number of words actulay marked deleted 
     * in the tree from given argument.
     */    
        function deleteWords($string){
            $count = 0;
            $words = preg_split("/[\s,]+/", $string);
            foreach($words as $word){   
                $word = trim($word);
                if(!empty($word)){
                    $count += $this->root->deleteWord($word, 0, strlen($word)-1);
                }
            }          
            return $count;
        }
    /*
     * method: printWords
     * This will accept one argument which specifies the string length wchi has to searched.
     * -1 will will print all the words present in the tree. 
     */
	function printWords($limit){
                $wordArray = array();
		$this->root->printWords($limit, '' , $wordArray);
                return $wordArray;
	}
}
?>