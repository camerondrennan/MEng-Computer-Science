package countdownpackage;

public class PlayCompleteGame {

	public static boolean completeGame = false;
	public static int completeScore = 0;
	public static int completeScorePone = 0;
	public static int completeScorePtwo = 0;
	public static boolean timeAct;
	public static boolean twoPlay;
	public static int letterRoundNo = 2;
	public static int numberRoundNo = 2;
	public static int conundrumRoundNo = 2;
	public static int letterRoundCount = 0;
	public static int numberRoundCount = 0;
	public static int conundrumRoundCount = 0;

	public static void main(String[] args) {
		System.out.println("************************");
		System.out.println("**WELCOME TO COUNTDOWN**");
		System.out.println("**        BY          **");
		System.out.println("**      STUART        **");
		System.out.println("**        &&          **");
		System.out.println("**      CAMERON       **");
		System.out.println("************************");
		//View highscores
		if(Round.viewHighscores()) {
			Highscores.getHighscores(Highscores.getReader());
		}
		
		timeAct = Round.timeYN();
		twoPlay = Round.twoPlayer();
		completeGame = Round.fullGame();

		if (completeGame) {
			if(Round.loadYN()){
				saveLoad.loadGame();
			}
			else{
				if(Round.customYN()) {
					System.out.println("How many times do you want to play each round?\n\nLetter Round:");
					letterRoundNo = Round.input.nextInt();
					System.out.println("Number Round:");
					numberRoundNo = Round.input.nextInt();
					System.out.println("Conundrum Round:");
					conundrumRoundNo = Round.input.nextInt();
				}
			}
			
			// Play Letter Round
			for (int a = 0; a < letterRoundNo; a++) {
				PlayLettersRound.playLetters(timeAct, twoPlay);
				if (twoPlay == true) {
					completeScorePone += PlayLettersRound.scorePone;
					System.out.println("Player one, your current score is: "
							+ PlayCompleteGame.completeScorePone);
					completeScorePtwo += PlayLettersRound.scorePtwo;
					System.out.println("Player two, your current score is: "
							+ PlayCompleteGame.completeScorePtwo);
					

				} else {
					completeScore += PlayLettersRound.score;
					System.out.println("Your current score: " + PlayCompleteGame.completeScore);
				}
				letterRoundCount++;
				if(Round.saveYN()){
					saveLoad.saveGame();
				}
			}

			// Play Number Round
			for (int b = 0; b < numberRoundNo; b++) {
				PlayNumbersRound.playNumbers(timeAct, twoPlay);
				if (twoPlay == true) {
					completeScorePone += PlayNumbersRound.scorePone;
					System.out.println("Player one, your current score is: "
							+ PlayCompleteGame.completeScorePone);
					completeScorePtwo += PlayNumbersRound.scorePtwo;
					System.out.println("Player two, your current score is: "
							+ PlayCompleteGame.completeScorePtwo);

				} else {
				completeScore += PlayNumbersRound.score;
				System.out.println("Your current score: " + PlayCompleteGame.completeScore);
				}
				numberRoundCount++;
				if(Round.saveYN()){
					saveLoad.saveGame();
				}
			}

			// Play Conundrum
			for (int c = 0; c < conundrumRoundNo; c++) {
				PlayConundrum.playConundrum(timeAct, twoPlay);
				if (twoPlay == true) {
					completeScorePone += PlayConundrum.scorePone;
					System.out.println("Player one your current score is: "
							+ PlayCompleteGame.completeScorePone);
					completeScorePtwo += PlayConundrum.scorePtwo;
					System.out.println("Player two your current score is: "
							+ PlayCompleteGame.completeScorePtwo);

				} else {
					completeScore += PlayConundrum.score;
					System.out.println("Your current score: "
							+ PlayCompleteGame.completeScore);
				}
				conundrumRoundCount++;
				if(Round.saveYN()){
					saveLoad.saveGame();
				}
			}
			if(letterRoundNo == 2 && numberRoundNo == 2 && conundrumRoundNo == 2 && twoPlay == false) {
				Highscores.addHighscore(PlayCompleteGame.completeScore);
				System.out.println("Highscore added");
			}
			else if(letterRoundNo == 2 && numberRoundNo == 2 && conundrumRoundNo == 2 && twoPlay == true) {
				Highscores.addHighscore(PlayCompleteGame.completeScorePone);
				Highscores.addHighscore(PlayCompleteGame.completeScorePtwo);
				System.out.println("Highscore added");
			}
			// End Game
			Round.input.close();
		} else {
			switch (Round.game()) {
			case (1):
				PlayLettersRound.playLetters(timeAct, twoPlay);
				break;
			case (2):
				PlayNumbersRound.playNumbers(timeAct, twoPlay);
				break;
			case (3):
				PlayConundrum.playConundrum(timeAct, twoPlay);
				break;
			default:
				System.out.println("Round.game() didn't return 1 2 or 3. It returned: "
							+ Round.game());
			}
		}
	}
}
