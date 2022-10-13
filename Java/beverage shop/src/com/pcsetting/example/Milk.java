package com.pcsetting.example;

public class Milk extends DrinkDecorator {

	Beverage beverage ;
	
	public Milk( Beverage beverage ) {
		// TODO Auto-generated constructor stub
		this.beverage = beverage ;
	}

	@Override
	public String getIngredient() {
		// TODO Auto-generated method stub
		return beverage.getIngredient() + ", Milk"  ;
	}

	@Override
	public int getCost() {
		// TODO Auto-generated method stub
		return 20 + beverage.getCost() ;
	}

}
