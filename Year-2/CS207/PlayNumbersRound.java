package countdownpackage;

import java.util.*;

public class PlayNumbersRound {
	static Random rGenerator = new Random();
	private static ArrayList<Integer> playerNumbers = new ArrayList<Integer>();
	private static ArrayList<String> operators = new ArrayList<String>();
	static int[] largeNumbers = { 25, 50, 75, 100 };
	static int target;
	static Scanner numberInput = new Scanner(System.in);
	static int stepNum = 1;
	static int score = 0;
	static int scorePone = 0;
	static int scorePtwo = 0;

	public static void playNumbers(boolean timeonoff, boolean twoPlay) {
		System.out.println("\n***************************");
		System.out.println("**WELCOME TO NUMBER ROUND**");
		System.out.println("**          BY           **");
		System.out.println("**        STUART         **");
		System.out.println("**          &&           **");
		System.out.println("**        CAMERON        **");
		System.out.println("***************************");
		score = 0;
		playerNumbers.clear();
		int j = 0;
		while (!playerNumbers.isEmpty()) {
			playerNumbers.remove(j);
			j++;
		}
		if (operators.isEmpty() == true) {
			operators.add("+");
			operators.add("-");
			operators.add("*");
			operators.add("/");
		}
		int command = 0;
		System.out.println("\nLARGE NUMBERS? [0-4]");
		command = numberInput.nextInt();

		if (command > 4 || command < 0) {
			System.out
					.println("*\nERROR Number of large numbers must be between 0 and 4.\n*");
			playNumbers(timeonoff, twoPlay);
			return;
		} else {
			for (int i = 0; i < command; i++) {
				int onetofour = rGenerator.nextInt(4);
				while (playerNumbers.contains(largeNumbers[onetofour])) {
					onetofour = rGenerator.nextInt(4);
				}
				playerNumbers.add(largeNumbers[onetofour]);
			}
			for (int i = 0; i < 6 - command; i++) {
				int remainingNos = rGenerator.nextInt((10 - 1) + 1) + 1;
				while ((Collections.frequency(playerNumbers, remainingNos)) > 1) {
					remainingNos = rGenerator.nextInt((10 - 1) + 1) + 1;
				}
				playerNumbers.add(remainingNos);
			}
		}
		generateTarget(timeonoff, twoPlay);
	}

	public static void generateTarget(boolean timeonoff, boolean twoPlay) {
		target = 0;
		target = rGenerator.nextInt((999 - 101) + 1) + 101;

		if (timeonoff == true) {
			System.out.println("**********");
			System.out.println("\nTARGET: " + target + ". You have 30 seconds to reach this target.");
			System.out.println("**********");
			Round.thirtysecs();
		} else {
			System.out.println("**********");
			System.out.println("\nTARGET: " + target);
			System.out.println("**********");
		}
		maths(timeonoff, twoPlay);
	}

	public static void maths(boolean timeonoff, boolean twoPlay) {
		System.out.println("\nNumbers:\n" + playerNumbers);
		System.out.println("Operators:\n" + operators);

		System.out.println("\nStep " + stepNum
				+ " (put spaces between operators and numbers)");

		int firstNInt = numberInput.nextInt();
		String operatorN = numberInput.next();
		int secondNInt = numberInput.nextInt();

		if (!playerNumbers.contains(firstNInt)
				|| !operators.contains(operatorN)
				|| !playerNumbers.contains(secondNInt)) {
			System.out
					.println("Error, operator not recognised or number is not in list");
			maths(timeonoff, twoPlay);
		} else {
			int stepNTotal = 0;
			switch (operatorN) {
			case "+":
				stepNTotal = firstNInt + secondNInt;
				break;
			case "-":
				stepNTotal = firstNInt - secondNInt;
				break;
			case "*":
				stepNTotal = firstNInt * secondNInt;
				break;
			case "/":
				stepNTotal = firstNInt / secondNInt;
				break;
			default:
				System.out.println("Something didn't work correctly...");
			}
			playerNumbers.remove(playerNumbers.indexOf(firstNInt));
			playerNumbers.remove(playerNumbers.indexOf(secondNInt));
			playerNumbers.add(stepNTotal);
		}

		if (playerNumbers.get(playerNumbers.size() - 1) == target) {
			score += 10;
			System.out.println("Congrats, You scored 10 points!");
			Round.playAgain("number", timeonoff, twoPlay);
		} else {
			System.out.println("= "
					+ playerNumbers.get(playerNumbers.size() - 1));
			System.out.println("Was this your final step? [Y/N]");
			String stepCondition = numberInput.next();
			switch (stepCondition.toUpperCase()) {
			case "Y":
				stepNum = 1;
				System.out.println("Your answer: "
						+ playerNumbers.get(playerNumbers.size() - 1));
				if (((playerNumbers.get(playerNumbers.size() - 1)) - target) <= 5
						&& ((playerNumbers.get(playerNumbers.size() - 1)) - target) >= -5) {
					score += 7;
					System.out.println("Congrats, You scored 7 points!");
					if (PlayCompleteGame.completeGame == false) {
						System.out.println("Your score: " + score);
					}
				} else if (((playerNumbers.get(playerNumbers.size() - 1)) - target) <= 10
						&& ((playerNumbers.get(playerNumbers.size() - 1)) - target) >= -10) {
					score += 5;
					System.out.println("Congrats, You scored 5 points!");
					if (PlayCompleteGame.completeGame == false) {
						System.out.println("Your score: " + score);
					}
				} else {
					System.out.println("Unlucky, You score 0 points");
					if (PlayCompleteGame.completeGame == false) {
						System.out.println("Your score: " + score);
					}
				}
				Round.playAgain("number", timeonoff, twoPlay);
				break;
			case "N":
				stepNum++;
				maths(timeonoff, twoPlay);
				break;

			default:
				System.out.println("Error, enter [Y/N]");
				maths(timeonoff, twoPlay);
				break;
			}
		}
		return;
	}

}
