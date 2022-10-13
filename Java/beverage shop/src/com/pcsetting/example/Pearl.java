package com.pcsetting.example;

public class Pearl extends DrinkDecorator {

	Beverage beverage ;
	
	public Pearl ( Beverage beverage ) {
		// TODO Auto-generated method stub
		this.beverage = beverage ;
	}
	
	@Override
	public String getIngredient() {
		// TODO Auto-generated method stub
		return beverage.getIngredient() + ", Pearl" ;
	}
	
	@Override
	public int getCost() {
		// TODO Auto-generated method stub
		return 10 + beverage.getCost() ;
	}

}
