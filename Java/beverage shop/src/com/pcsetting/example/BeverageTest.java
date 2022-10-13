package com.pcsetting.example;

public class BeverageTest {

	public static void main(String[] args) {
		// TODO Auto-generated method stub
		Beverage beverage1, beverage2, beverage3 ;
		
		// 開始製作無糖珍珠紅茶拿鐵
		beverage1 = new BlackTea() ;
		beverage1 = new Milk( beverage1 ) ;
		beverage1 = new Pearl( beverage1 ) ;
		System.out.println( "Ingredient: " + beverage1.getIngredient() ) ;
		System.out.println( "Prices: " + beverage1.getCost() ) ;
		
		// 開始製作有糖奶綠
		beverage2 = new GreenTea() ;
		beverage2 = new Milk( beverage2 ) ;
		beverage2 = new Pearl( beverage2 ) ;
		beverage2 = new Sugar( beverage2 ) ;
		System.out.println( "Ingredient: " + beverage2.getIngredient() ) ;
		System.out.println( "Prices: " + beverage2.getCost() ) ;
		
		// 開始製作有糖重乳紅茶拿鐵
		beverage3 = new BlackTea() ;
		beverage3 = new Milk( beverage3 ) ;
		beverage3 = new Milk( beverage3 ) ;
		beverage3 = new Sugar( beverage3 ) ;
		System.out.println( "Ingredient: " + beverage3.getIngredient() ) ;
		System.out.println( "Prices: " + beverage3.getCost() ) ;
	}

}
