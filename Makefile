.PHONY: clean All

All:
	@echo "----------Building project:[ AStar - Debug ]----------"
	@cd "AStar" && "$(MAKE)" -f  "AStar.mk"
clean:
	@echo "----------Cleaning project:[ AStar - Debug ]----------"
	@cd "AStar" && "$(MAKE)" -f  "AStar.mk" clean
