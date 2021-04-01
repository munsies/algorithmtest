.PHONY: clean All

All:
	@echo "----------Building project:[ LeftTurnGrid - Debug ]----------"
	@cd "LeftTurnGrid" && "$(MAKE)" -f  "LeftTurnGrid.mk"
clean:
	@echo "----------Cleaning project:[ LeftTurnGrid - Debug ]----------"
	@cd "LeftTurnGrid" && "$(MAKE)" -f  "LeftTurnGrid.mk" clean
