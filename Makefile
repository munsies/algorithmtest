.PHONY: clean All

All:
	@echo "----------Building project:[ SearchGrid - Debug ]----------"
	@cd "SearchGrid" && "$(MAKE)" -f  "SearchGrid.mk"
clean:
	@echo "----------Cleaning project:[ SearchGrid - Debug ]----------"
	@cd "SearchGrid" && "$(MAKE)" -f  "SearchGrid.mk" clean
