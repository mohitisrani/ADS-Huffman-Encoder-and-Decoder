// since the size of info varibles to be encoded is known
// binary heap can be made using an array of size 10 instead of an arraylist
//

import java.util.Random;
import java.util.HashMap;
import java.util.Map;
import java.util.Scanner;

class Node{
	public Integer val;
	public int freq;
	public Node(Integer val){
		this.val = val;
		freq = 0;
	}
	Node left = null;
	Node right = null;
}

interface PriorityQueue{
	public int peekMinVal();
	public Node extractMinNode();
	public void printBinaryHeap();
	public Node insert(int freq);
	public int size();
}

class BinaryHeap implements PriorityQueue{
	private Node[] heap = new Node[10];
	private int heapSize = 0;
	public BinaryHeap(Node [] frequencyTable){
		for(int i=0;i<frequencyTable.length;i++){
			heap[i]=frequencyTable[i];
		}
		heapSize = frequencyTable.length;
		for(int i = (heapSize-1)/2;i>=0;i--){
			heapifyDown(i);
		}
	}
	
	public int size(){
		return heapSize;
	}
	
	private void heapifyDown(int i){
		int iLeft = i*2+1, iRight = i*2+2;
		int left = iLeft < heapSize ? heap[iLeft].freq : Integer.MAX_VALUE;
		int right = iRight <heapSize ? heap[iRight].freq : Integer.MAX_VALUE;
		Node temp;
		if(left<right){
			if(heap[i].freq > left){
				temp = heap[iLeft];
				heap[iLeft] = heap[i];
				heap[i] = temp;
				heapifyDown(iLeft);
			}
		}else{
			if(heap[i].freq > right){
				temp = heap[iRight];
				heap[iRight] = heap[i];
				heap[i] = temp;
				heapifyDown(iRight);
			}
		}		
	}
	
	private void heapifyUp(int i){
		int iParent = (i-1)/2;
		if(iParent!=-1){
			if(heap[iParent].freq>heap[i].freq){
				Node temp = heap[iParent];
				heap[iParent] = heap[i];
				heap[i] = temp;
				heapifyUp(iParent);
			}
		}
	}
	
	public Node insert(int freq){
		Node temp=new Node(null);
		temp.freq = freq;
		heap[heapSize] = temp;
		heapifyUp(heapSize++);
		return temp;
	}
	
	public int peekMinVal(){
		if(heapSize==0){
			return -1;
		}
		return heap[0].val;
	}
	
	public Node extractMinNode(){
		if(heapSize==0){
			return null;
		}else if(heapSize==1){
			heapSize--;
			return heap[0];
		}else{
			Node toReturn = heap[0];
			heap[0] = heap[--heapSize];
			heapifyDown(0);
			return toReturn;
		}
	}
	
	public void printBinaryHeap(){
		for(int i =0;i<heapSize;i++){
			System.out.print(heap[i].freq+" ");
		}
		System.out.println();
	}
}




class HuffmanTree{
	public HuffmanTree(PriorityQueue pq){
		while(pq.size()!=1){
			Node left = pq.extractMinNode();
			Node right = pq.extractMinNode();
			Node temp = pq.insert(left.freq+right.freq);
			temp.left = left;
			temp.right = right;
		}
		root = pq.extractMinNode();
	}
	public Node root;
}

class Encoder{
	private Map<Integer,String> map= new HashMap<>();
	private StringBuilder code = new StringBuilder();
	public Encoder(HuffmanTree ht){
		Node root = ht.root;
		StringBuilder sb = new StringBuilder();
		inorder(root,sb,0);
		
	}
	private void inorder(Node root,StringBuilder sb,int size){
		if(root.val!=null){
			map.put(root.val,sb.toString());
			return;
		}else{
			if(root.left!=null){
				sb.append('0');
				inorder(root.left,sb,size+1);
				sb.deleteCharAt(size);
			}
			if(root.right!=null){
				sb.append('1');
				inorder(root.right,sb,size+1);
				sb.deleteCharAt(size);
			}
		}
	}
	
	public void encode(String s){
		for(char c: s.toCharArray()){
			code.append(map.get(c-'0'));
		}
	}
	public void encode(char c){
		code.append(map.get(c-'0'));
	}
	public void encode(Integer i){
		code.append(map.get(i));
	}
	
	public void printCode(){
		System.out.println("The coded value is: \n" + code.toString());
	}
	
	public void printEncoder(){
		for(Map.Entry<Integer,String> entry: map.entrySet()){
			System.out.println(String.valueOf(entry.getKey()) + " "+ entry.getValue());
		}
	}
	
	public StringBuilder outputCodeStringBuilder(){
		return code;
	}
}

class Decoder{
	Node decoderTreeRoot;
	Decoder(HuffmanTree ht){
		decoderTreeRoot = ht.root;
	}
	
	void decode(StringBuilder code){
		int size = code.length();
		Node root = decoderTreeRoot;
		StringBuilder decodedText = new StringBuilder();
		for(int i=0;i<size;i++){
			if(code.charAt(i)=='0'){
				root = root.left;
			}else{
				root = root.right;
			}
			if(root.val!=null){
				decodedText.append(root.val);
				root = decoderTreeRoot;
			}
		}
		System.out.println("Decoded Text: \n" + decodedText.toString()+"\n");
	}
}







class Test{
	public static void main(String [] args){
		Node[] frequencyTable = new Node[10];
		
		Random f = new Random();
		for(int i=0;i<frequencyTable.length;i++){
			frequencyTable[i]=new Node(i);
			frequencyTable[i].freq = f.nextInt(100);
			// System.out.print(frequencyTable[i].freq+" ");
		}// System.out.println();
		
		
		PriorityQueue pq = new BinaryHeap(frequencyTable);
		// pq.printBinaryHeap();
		
		/*
		Node left = pq.extractMinNode();
		Node right = pq.extractMinNode();
		Node temp = pq.insert(left.freq+right.freq);
		temp.left = left;
		temp.right = right;
		
		*/
		HuffmanTree ht = new HuffmanTree(pq);
		// System.out.println(ht.root.freq);
		// pq.printBinaryHeap(); it gets empty after creating HuffmanTree
		
		Encoder encoder = new Encoder(ht);
		Decoder decoder = new Decoder(ht);
		
		// encoder.printEncoder();
		
		System.out.println();
		System.out.println("Enter the text to be encoded(number)");
		Scanner in = new Scanner(System.in);
		encoder.encode(in.next());
		System.out.println();
		encoder.printCode();
		
		System.out.println();
		StringBuilder code  = encoder.outputCodeStringBuilder();
		decoder.decode(code);
		
		
	}
}