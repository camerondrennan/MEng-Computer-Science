package countdownpackage;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Collections;

public class Highscores {
	
	private static ArrayList<Integer> scoreArr = new ArrayList<Integer>();
	
	public static BufferedReader getReader() {
    	FileReader fr = null;
		try {
			fr = new FileReader("highscores.txt");
		} 
		catch (FileNotFoundException e) {
			System.out.println("*File not found*");
		}
    	BufferedReader reader = new BufferedReader(fr);
    	return reader;
    }
	
	public static void getHighscores(BufferedReader br) {
		int position = 1;
		try {
			String score = br.readLine();
			System.out.println("\n***************");
			System.out.println("HIGHSCORES:");
			while(!score.equals(null)) {
				System.out.println(position + ". " + score);
				position++;
				score = br.readLine();
			}
			System.out.println("***************");
		} 
		catch (IOException e) {
			System.out.println("*Input/Output Error*");
		}
		catch (NullPointerException e1) {
		}
	}
	
	  
	public static void writeHighscores() {	
		int i;
		try {
			FileWriter fw = new FileWriter("highscores.txt");
			BufferedWriter writer = new BufferedWriter(fw);
			for(i = 0; i < scoreArr.size(); i++) {
				writer.write(scoreArr.get(i) + "\n");
			}
			writer.close();
		} 
		catch (IOException e) {
			System.out.println("*Input/Output Error*");
		}
	}
	
	public static void addHighscore(int hScore) {
		if(scoreArr.isEmpty()) {
			retainHighscores(getReader());
		}
		scoreArr.add(hScore);
		Collections.sort(scoreArr, Collections.reverseOrder());
		writeHighscores();
	}
	
	public static void retainHighscores(BufferedReader br1) {
		int prevIntScore;
		String prevStrScore;
		try {
			prevStrScore = br1.readLine();
			while(!prevStrScore.equals(null)) {
				prevIntScore = Integer.parseInt(prevStrScore);
				scoreArr.add(prevIntScore);
				prevStrScore = br1.readLine();
			}
		} 
		catch (IOException e) {
			System.out.println("*Input/Output Error*");
		}
		catch (NullPointerException e1) {
		}
	}
	
	public static void main(String[] args) {
		addHighscore(10000);
		addHighscore(10000000);
		getHighscores(getReader());
	}   
}
