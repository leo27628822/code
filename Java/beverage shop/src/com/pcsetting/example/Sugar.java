package com.pcsetting.example;

public class Sugar extends DrinkDecorator {

	Beverage beverage ;
	
	public Sugar( Beverage beverage ) {
		// TODO Auto-generated constructor stub
		this.beverage = beverage ;
	}

	@Override
	public String getIngredient() {
		// TODO Auto-generated method stub
		return beverage.getIngredient() + ", Sugar"  ;
	}

	@Override
	public int getCost() {
		// TODO Auto-generated method stub
		return 5 + beverage.getCost() ;
	}

}
