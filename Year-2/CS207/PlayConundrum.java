package countdownpackage;

import java.io.*;
import java.util.*;

public class PlayConundrum {
	private static ArrayList<String> conundrumList = new ArrayList<String>();
	private static String conundrumSorted;
	private static String shuffledConundrum;
	static Random rGenerator = new Random();
	static int score = 0;
	static int scorePone = 0;
	static int scorePtwo = 0;
	static Scanner conundrumInput = new Scanner(System.in);

	public static BufferedReader dictionaryReader()
			throws FileNotFoundException {
		FileReader fr = new FileReader("smalldictionary.txt");
		BufferedReader reader = new BufferedReader(fr);
		return reader;
	}

	private static void generateConundrum(BufferedReader br) throws IOException {
		String token = br.readLine();
		while (token != null) {
			if (token.length() == 9) {
				conundrumList.add(token);
			}
			token = br.readLine();
		}
		for (int i = 0; i < conundrumList.size(); i++) {
			int randNum = rGenerator.nextInt(conundrumList.size() - 1);
			conundrumSorted = conundrumList.get(randNum);
		}
		ArrayList<Character> chars = new ArrayList<Character>(
				conundrumSorted.length());
		for (char c : conundrumSorted.toCharArray()) {
			chars.add(c);
		}
		Collections.shuffle(chars);
		char[] shuffled = new char[chars.size()];
		for (int i = 0; i < shuffled.length; i++) {
			shuffled[i] = chars.get(i);
		}
		shuffledConundrum = new String(shuffled);
	}

	public static void playConundrum(boolean timer, boolean twoPlay) {
		System.out.println("\n******************************");
		System.out.println("**WELCOME TO CONUNDRUM ROUND**");
		System.out.println("**            BY            **");
		System.out.println("**          STUART          **");
		System.out.println("**            &&            **");
		System.out.println("**          CAMERON         **");
		System.out.println("******************************");
		score = 0;
		boolean timeonoff = timer;
		try {
			generateConundrum(dictionaryReader());
		} catch (FileNotFoundException e1) {
			System.out.println(e1.toString());
		} catch (IOException e1) {
			System.out.println(e1.toString());
		}
		if (timeonoff == true) {
			System.out.println("\nYour conundrum is:\n" + shuffledConundrum
					+ ". Please do not answer until timer is up!");
			Round.thirtysecs();
		} else {
			System.out.println("\nYour conundrum is:\n" + shuffledConundrum);
		}
		if (twoPlay == true) {
			System.out.println("Which player wishes to answer? [1/2]");
			String poneortwo;
			poneortwo = conundrumInput.nextLine();

			if (poneortwo.equals("1")) {
				System.out.println("Please enter your answer player one:");
				String commandPone = "";
				commandPone = conundrumInput.nextLine();
				char[] char1Pone = commandPone.toCharArray();
				char[] char2Pone = shuffledConundrum.toCharArray();
				Arrays.sort(char1Pone);
				Arrays.sort(char2Pone);
				if (Arrays.equals(char1Pone, char2Pone) == true
						&& conundrumList.contains(commandPone)) {
					scorePone = scorePone + 10;
					System.out.println("Congrats player one, your score is: " + scorePone);
				} else {
					System.out.println("Rubbish, it was supposed to be "
							+ conundrumSorted);
					if (PlayCompleteGame.completeGame == false) {
						System.out.println("Your score: " + scorePone);
					}
				}

			} else if(poneortwo.equals("2")){
				System.out.println("Please enter your answer player two:");
				String commandPtwo = "";
				commandPtwo = conundrumInput.nextLine();
				char[] char1Ptwo = commandPtwo.toCharArray();
				char[] char2Ptwo = shuffledConundrum.toCharArray();
				Arrays.sort(char1Ptwo);
				Arrays.sort(char2Ptwo);
				if (Arrays.equals(char1Ptwo, char2Ptwo) == true
						&& conundrumList.contains(commandPtwo)) {
					scorePtwo = scorePtwo + 10;
					System.out.println("Congrats player two, your score is: " + scorePtwo);
				} else {
					System.out.println("Rubbish, it was supposed to be "
							+ conundrumSorted);
					if (PlayCompleteGame.completeGame == false) {
						System.out.println("Your score: " + scorePtwo);
					}
				}
			} else {
				System.out.println("Invalid answer.");
				poneortwo = conundrumInput.nextLine();
			}

		} else {
			String command = "";
			command = conundrumInput.nextLine();
			char[] char1 = command.toCharArray();
			char[] char2 = shuffledConundrum.toCharArray();
			Arrays.sort(char1);
			Arrays.sort(char2);
			if (Arrays.equals(char1, char2) == true
					&& conundrumList.contains(command)) {
				score = score + 10;
				System.out.println("Congrats, your score is: " + score);
			} else {
				System.out.println("Rubbish, it was supposed to be "
						+ conundrumSorted);
				if (PlayCompleteGame.completeGame == false) {
					System.out.println("Your score: " + score);
				}
			}
		}
		Round.playAgain("conundrum", timeonoff,twoPlay);

	}
}
