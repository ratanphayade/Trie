<?php
/*
 * Author: Ratan Phayade
 * This class will define the the Node structure which to be used in class TrieTree.
 * This call will provide the methods to asses the nodes and manages the link between them.
 */
class Node{
        
        public $value;
        public $finishesWord;
        public $children = array();
        /*
         * Default Constructor
         * Will initialize the node value to the value passed my the argument.
         */
	function __construct($inittialValue){ 
            $this->value = $inittialValue;            
        }
        /*
         * Method : addWord
         * Will accept one parameter and add the word to the tree.
         */
	function addWord($word, $index, $length){
		if($index < $length){
			$childNode = $this->getChildNode($word[$index]);
			$childNode = ($childNode)? $childNode : $this->addChildNode($word[$index]);
			$childNode->addWord($word, $index+1, $length);                        
		} else 
			$this->finishesWord = TRUE;
        }
        /*
         * method: hasWord
         * Check whether the passed word is present in the tree or not.
         */
	function hasWord($word, $index, $length){
                $childNode = $this->getChildNode($word[$index]);
		if($index < $length)
			return ($childNode)? $childNode->hasWord($word, $index+1, $length) : FALSE;
		else
			return $childNode->finishesWord;		
	}		
        /*
         * method: getChildNode
         * Will accept a single charecter as a parameter and checks whether the charecter is present in its child.
         */
	function getChildNode($charecter) {
                return isset($this->children[$charecter])? $this->children[$charecter] : null;
	}
        /*
         * method: addChildNode
         * Addes a new child to the node if its not already present.
         */
	function addChildNode($charecter) {
                if(isset($this->children[$charecter])){
                    return $this->children[$charecter];
                } else {
                    $this->children[$charecter] = new Node($charecter);
                    return $this->children[$charecter];
                }
	}
        
        /*
         * method: printWords
         * will append the array fo string with all the word present in the tree
         * for a given limit.
         */
 
	function printWords($limit, $prefix, &$wordArray){
		if($this->finishesWord)
			$wordArray[] = $prefix.$this->value.'<br/>';
		if(is_array($this->children) && $limit){
			foreach($this->children as $child){
				$child->printWords($limit-1 ,$prefix.$this->value, $wordArray);
			}
		}
	}
        /*
         * method: deleteWord
         * Will mark a word deleted.
         */
        function deleteWord($word, $index, $length){
                $childNode = $this->getChildNode($word[$index]);
		if($index < $length)
			return ($childNode)? $childNode->deleteWord($word, $index+1, $length) : 0;
		else {
			if($childNode->finishesWord){
                            $childNode->finishesWord = FALSE;
                            return 1;
                        } else 
                            return 0;
                }
	}
}

?>