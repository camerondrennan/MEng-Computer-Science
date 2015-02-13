package countdownpackage;

import java.util.Scanner;
import java.util.Timer;
import java.util.TimerTask;

public class Round {
	static long delay;
	static Timer timer;
	static Scanner input = new Scanner(System.in);

	public static int game() {
		System.out.println("\n********************************");
		System.out.println("*****CHOOSE A GAME TO PLAY?*****\n1 - Letter Round\n2 - Number Round\n3 - Conundrum\nEnter [1 or 2 or 3]");
		System.out.println("********************************");
		int gameKind;
		gameKind = input.nextInt();
		if (gameKind == 1 || gameKind == 2 || gameKind == 3) {
			return gameKind;
		} else {
			System.out.println("Invalid answer. Type [Y/N]");
			game();
		}
		return gameKind;
	}

	public static boolean viewHighscores() {
		System.out.println("\nVIEW HIGHSCORES? [Y/N]");
		String viewYesNo = input.nextLine();
		if (viewYesNo.toUpperCase().equals("Y")) {
			return true;
		} else if (viewYesNo.toUpperCase().equals("N")) {
			return false;
		} else {
			System.out.println("Invalid answer. Type [Y/N]");
			viewHighscores();
		}
		return false;
	}

	public static boolean customYN() {
		System.out.println("\nCUSTOM NO. ROUNDS? [Y/N] (note score will not be included in highscores)");
		String customYesNo = input.nextLine();
		if (customYesNo.toUpperCase().equals("Y")) {
			return true;
		} else if (customYesNo.toUpperCase().equals("N")) {
			return false;
		} else {
			System.out.println("Invalid answer. Type [Y/N]");
			customYN();
		}
		return false;
	}

	public static boolean timeYN() {
		System.out.println("\nTIMER? [Y/N]");
		String timerYesNo = "";
		timerYesNo = input.nextLine();
		if (timerYesNo.toUpperCase().equals("Y")) {
			return true;
		} else if (timerYesNo.toUpperCase().equals("N")) {
			return false;
		} else {
			System.out.println("Invalid answer. Type [Y/N]");
			timeYN();
		}
		return false;

	}
	
	public static boolean loadYN() {
		System.out.println("\nLOAD GAME? [Y/N]");
		String loadYesNo = "";
		loadYesNo = input.nextLine();
		if (loadYesNo.toUpperCase().equals("Y")) {
			return true;
		} else if (loadYesNo.toUpperCase().equals("N")) {
			return false;
		} else {
			System.out.println("Invalid answer. Type [Y/N]");
			loadYN();
		}
		return false;

	}
	
	public static boolean saveYN() {
		System.out.println("\nSAVE GAME? [Y/N]");
		String saveYesNo = input.nextLine();
		System.out.println(saveYesNo);
		if (saveYesNo.toUpperCase().equals("Y")) {
			return true;
		} else if (saveYesNo.toUpperCase().equals("N")) {
			return false;
		}
		else {
			saveYesNo = input.nextLine();
			if (saveYesNo.toUpperCase().equals("Y")) {
				return true;
			} else if (saveYesNo.toUpperCase().equals("N")) {
				return false;
			} else if (!saveYesNo.toUpperCase().equals("Y") || !saveYesNo.toUpperCase().equals("N")){
				System.out.println("Invalid answer. Type [Y/N]");
				saveYN();
			}
		}
		return false;

	}

	public static boolean twoPlayer() {
		System.out.println("\nTWO PLAYER? [Y/N]");
		String twoYesNo = "";
		twoYesNo = input.nextLine();
		if (twoYesNo.toUpperCase().equals("Y")) {
			return true;
		} else if (twoYesNo.toUpperCase().equals("N")) {
			return false;
		} else {
			System.out.println("Invalid answer. Type [Y/N]");
			twoPlayer();
		}
		return false;
	}

	public static boolean fullGame() {
		System.out.println("\nFULL GAME? [Y/N]");
		String gameType = input.nextLine();
		if (gameType.toUpperCase().equals("Y")) {
			return true;
		} else if (gameType.toUpperCase().equals("N")) {
			return false;
		} else {
			System.out.println("Invalid answer. Type [Y/N]");
			fullGame();
		}
		return false;
	}

	public static void thirtysecs() {
		timer = new Timer();
		/* in ms so /1000 */
		delay = 30000;
		timer.schedule(new TimerTask() {

			public void run() {
				System.out.println("Time up! Enter your answer:");

			}
		}, delay);
	}

	public static void playAgain(String game, boolean timeonoff, boolean twoPlay) {
		if (PlayCompleteGame.completeGame == false) {
			System.out.println("PLAY AGAIN? [Y/N] ");
			String replay = "";
			replay = input.nextLine();
			replay = input.nextLine();
			if (replay.toUpperCase().equals("Y")) {
				if (game.equals("letter")) {
					PlayLettersRound.playLetters(timeonoff, twoPlay);
				} else if (game.equals("number")) {
					PlayNumbersRound.playNumbers(timeonoff, twoPlay);
				} else if (game.equals("conundrum")) {
					PlayConundrum.playConundrum(timeonoff, twoPlay);
				}
			} else if (replay.toUpperCase().equals("N")) {
				if (game.equals("letter")) {
					if (twoPlay == true) {
						System.out.println("Thanks for playin'! Player one your score is: "
									+ PlayLettersRound.scorePone + " and player two your score is: "+PlayLettersRound.scorePtwo);
						input.close();

					} else {
						System.out.println("Thanks for playin'! your score is: "
									+ PlayLettersRound.score);
						input.close();
					}
				} else if (game.equals("number")) {
					if (twoPlay == true) {
						System.out.println("Thanks for playin'! Player one your score is: "
									+ PlayNumbersRound.scorePone + " and player two your score is: "+PlayNumbersRound.scorePtwo);
						input.close();

					} else {
						System.out.println("Thanks for playin'! your score is: "
									+ PlayNumbersRound.score);
						input.close();
					}
				} else if (game.equals("conundrum")) {
					if (twoPlay == true) {
						System.out.println("Thanks for playin'! Player one your score is: "
									+ PlayConundrum.scorePone + " and player two your score is: "+PlayConundrum.scorePtwo);
						input.close();

					} else {
						System.out.println("Thanks for playin'! your score is: "
								+ PlayConundrum.score);
						input.close();
					}
				}
			} else {
				System.out.println("Invalid answer. Type [Y/N]");
				playAgain(game, timeonoff, twoPlay);
			}
		}
	}
}
