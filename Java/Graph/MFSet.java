
	
public class MFSet<T>{


	int [] array; 

	// evaluates the index (in the array) for T
	Indexer<T> indexer;
	
	public MFSet(int size, Indexer<T> indexer){
		this.array = new int[size];
		reset(0);
		this.indexer = indexer;
	}

	/*
		merge two elements
		parent of elm1 becomes parent of elm2's parent
		
	*/
	public void merge(T elm1, T elm2){

		int parent1 = find(elm1);
		int parent2 = find(elm2);
		
		array[parent1] += array[parent2];
		array[parent2] = parent1;
	}

	// finds and returns the parent of elm
	public int find(T elm){
		// elm's index
		int index = indexer.eval(elm);
		int temp = array[index];
		while(temp >= 0){
			index = temp;
			temp = array[temp];
			if(temp >= 0)
				index = temp;
		}
		return index;
	}

	// must return unique seqential indexies for each element
	public interface Indexer<T>{
		public int eval(T elm);
	}
	
	/*
	increses the array if elemsts is larger than the length of the array
	sets all indexes in the array to -1
	*/
	public void reset(int elements){
		if(elements <= array.length){
			for(int i = 0; i < array.length; i++){
				array[i] = -1;
			}
		}else{
			array = new int[elements];
			for(int i = 0; i < elements; i++){
				array[i] = -1;
			}
		}
		
	}

	public int size(){
		return array.length;
	}
}
