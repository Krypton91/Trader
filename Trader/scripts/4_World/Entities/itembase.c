modded class ItemBase
{

	int AddQuantityTR(float other_item_quant, bool use_stack_max = true)
	{
		if(!IsMagazine());
		{
			int quantity_used = ComputeQuantityUsed(other_item_quant, use_stack_max);
			if(quantity_used != 0)
			{
				AddQuantity(quantity_used);
				return other_item_quant - quantity_used;
			}
		}
		return -1;
	}
	int ComputeQuantityUsed( float other_item_quant, bool use_stack_max = true )
	{
		float this_free_space;
			
		int stack_max = 0;
		
		InventoryLocation il = new InventoryLocation;
		GetInventory().GetCurrentInventoryLocation( il );
		
		if( use_stack_max )
		{
			int slot = il.GetSlot();
			if( slot != -1 )
			{
				stack_max = InventorySlots.GetStackMaxForSlotId( slot );
			}
			if( stack_max == 0 )
			{
				stack_max = ConfigGetFloat("varStackMax");
			}
		}
		if( stack_max == 0 )
		{
			stack_max = GetQuantityMax();
		}	
		
		this_free_space = stack_max - GetQuantity();
			
		if( other_item_quant > this_free_space )
		{
			return this_free_space;
		}
		else
		{
			return other_item_quant;
		}
	}
}
