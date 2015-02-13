package countdownpackage;

import java.io.BufferedWriter;
import java.io.File;
import java.io.FileWriter;
import java.io.IOException;
import java.util.Scanner;

public class saveLoad {

	public static void loadGame() {
		if (PlayCompleteGame.twoPlay == true) {
			try {
				Scanner gameLoaderMul = new Scanner(new File("savegameMult.txt"));

				PlayCompleteGame.completeScorePone = gameLoaderMul.nextInt();
				PlayCompleteGame.completeScorePtwo = gameLoaderMul.nextInt();
				PlayCompleteGame.letterRoundNo = gameLoaderMul.nextInt();
				PlayCompleteGame.numberRoundNo = gameLoaderMul.nextInt();
				PlayCompleteGame.conundrumRoundNo = gameLoaderMul.nextInt();
				
				gameLoaderMul.close();

			} catch (IOException e) {
				System.out.println("*Input/Output Error*");
			} catch (NullPointerException e1) {
			}

		} else {
			try {
				Scanner gameLoader = new Scanner(new File("savegameSing.txt"));

				PlayCompleteGame.completeScore = gameLoader.nextInt();
				PlayCompleteGame.letterRoundNo = gameLoader.nextInt();
				PlayCompleteGame.numberRoundNo = gameLoader.nextInt();
				PlayCompleteGame.conundrumRoundNo = gameLoader.nextInt();
				
				gameLoader.close();

			} catch (IOException e) {
				System.out.println("*Input/Output Error*");
			} catch (NullPointerException e1) {
			}
		}
	}

	public static void saveGame() {
		System.out.println("Saving game!");
		if (PlayCompleteGame.twoPlay == true) {
			try {
				FileWriter fw = new FileWriter("savegameMult.txt");
				BufferedWriter writer = new BufferedWriter(fw);
				writer.write(PlayCompleteGame.completeScorePone + "\n");
				writer.write(PlayCompleteGame.completeScorePtwo + "\n");
				writer.write((PlayCompleteGame.letterRoundNo - PlayCompleteGame.letterRoundCount) + "\n");
				writer.write((PlayCompleteGame.numberRoundNo - PlayCompleteGame.numberRoundCount) + "\n");
				writer.write((PlayCompleteGame.conundrumRoundNo - PlayCompleteGame.conundrumRoundCount) + "\n");
				
				writer.close();

			} catch (IOException e) {
				System.out.println("*Input/Output Error*");
			}

		} else {
			try {
				FileWriter fw = new FileWriter("savegameSing.txt");
				BufferedWriter writer = new BufferedWriter(fw);
				writer.write(PlayCompleteGame.completeScore + "\n");
				writer.write((PlayCompleteGame.letterRoundNo - PlayCompleteGame.letterRoundCount) + "\n");
				writer.write((PlayCompleteGame.numberRoundNo - PlayCompleteGame.numberRoundCount) + "\n");
				writer.write((PlayCompleteGame.conundrumRoundNo - PlayCompleteGame.conundrumRoundCount) + "\n");
				writer.close();

			} catch (IOException e) {
				System.out.println("*Input/Output Error*");
			}
		}
	}
}
