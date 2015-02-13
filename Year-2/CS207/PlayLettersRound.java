package countdownpackage;

import java.io.BufferedReader;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.IOException;
import java.util.ArrayList;
import java.util.Random;
import java.util.Scanner;

public class PlayLettersRound {
	private static ArrayList<String> letterList = new ArrayList<String>();
	private static ArrayList<String> dictionary = new ArrayList<String>();
	static Scanner letterInput = new Scanner(System.in);
	static Random rGenerator = new Random();
	static String letters;
	static int score = 0;
	static int scorePone = 0;
	static int scorePtwo = 0;

	public static BufferedReader dictionaryReader() {
		FileReader fr = null;
		try {
			fr = new FileReader("dictionary.txt");
		} catch (FileNotFoundException e) {
			System.out.println(e.toString());
		}
		BufferedReader reader = new BufferedReader(fr);
		return reader;
	}

	public static void fillDictionary(BufferedReader br) {
		String word = null;
		try {
			word = br.readLine();
		} catch (IOException e) {
			System.out.println(e.toString());
		}
		while (word != null) {
			dictionary.add(word);
			try {
				word = br.readLine();
			} catch (IOException e) {
				System.out.println(e.toString());
			}
		}
	}

	public static String getLetterAnswer(boolean twoPlay) {

		String answer = letterInput.nextLine();
		if (checkAnswerLetters(answer, twoPlay) && dictionary.contains(answer)) {
			System.out.println("Well done!\n");
		} else if (dictionary.contains(answer)) {
			System.out.println("Word cannot be made using these letters\n");
			answer = "";
		} else if (checkAnswerLetters(answer, twoPlay)) {
			System.out.println("Word is not in dictionary\n");
			answer = "";
		} else {
			System.out.println("Word cannot be made using these letters and is not in dictionary\n");
			answer = "";
		}
		return answer;
	}

	public static boolean checkAnswerLetters(String ans, boolean twoPlay) {
		ArrayList<String> list = new ArrayList<String>();
		list.addAll(letterList);
		char[] char1 = ans.toCharArray();
		for (int i = 0; i < char1.length; i++) {
			if (list.contains(char1[i] + "")) {
				list.remove(char1[i] + "");
			} else {
				return false;
			}
		}
		return true;
	}

	public static BufferedReader letterReader(String filename, boolean timeonoff, boolean twoPlay) {
		FileReader fr = null;
		try {
			fr = new FileReader(filename + ".txt");
		} catch (FileNotFoundException e) {
			System.out.println(e.toString());
		}
		BufferedReader reader = new BufferedReader(fr);
		int randomNumber = 0;
		String letter = "";
		if (filename.equals("v")) {
			randomNumber = rGenerator.nextInt((5 - 1) + 1) + 1;
		}
		if (filename.equals("c")) {
			randomNumber = rGenerator.nextInt((21 - 1) + 1) + 1;
		}
		for (int i = 0; i < randomNumber; i++) {
			try {
				letter = reader.readLine();
			} catch (IOException e) {
				System.out.println(e.toString());
			}
		}
		letterList.add(letter);
		System.out.println(letter);
		playLetterRound(timeonoff, twoPlay);
		return reader;
	}

	private static void playLetterRound(boolean timeonoff, boolean twoPlay) {
		if (letterList.size() == 9) {
			letters = letterList.toString().replace(", ", "").replace("[", "")
					.replace("]", "");
			System.out.print("\nOK! here are your letters:\n");
			System.out.println(letters);
			if (timeonoff == true) {
				Round.thirtysecs();
			}
			if (timeonoff == true) {
				System.out.println("You have 30 seconds to enter your best answer! (Please do not enter answer until time is up!)\n");
			} else {
				System.out.println("");
			}

			if (twoPlay == true) {

				System.out.println("Player one please answer:");
				scorePone += getLetterAnswer(twoPlay).length();
				System.out.println("Player two please answer:");
				scorePtwo += getLetterAnswer(twoPlay).length();

				if (PlayCompleteGame.completeGame == false) {
					System.out.println("Player one, your score is: "
							+ scorePone);
					System.out.println("Player two, your score is: "
							+ scorePtwo);
				}
			} else {
				score += getLetterAnswer(twoPlay).length();

				if (PlayCompleteGame.completeGame == false) {
					System.out.println("Your score: " + score);
				}
			}
			letterList.clear();
			Round.playAgain("letter", timeonoff, twoPlay);
		} else {
			System.out.println("\nVOWEL OR CONSONANT? [V/C]");
			String command = letterInput.nextLine();
			letterReader(command, timeonoff, twoPlay);
		}
	}

	public static void playLetters(boolean timeonoff, boolean twoPlay) {
		fillDictionary(dictionaryReader());
		System.out.println("\n***************************");
		System.out.println("**WELCOME TO LETTER ROUND**");
		System.out.println("**          BY           **");
		System.out.println("**        STUART         **");
		System.out.println("**          &&           **");
		System.out.println("**        CAMERON        **");
		System.out.println("***************************");
		score = 0;
		playLetterRound(timeonoff, twoPlay);
	}
}
