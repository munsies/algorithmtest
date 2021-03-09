.PHONY: clean All

All:
	@echo "----------Building project:[ OccupacyGridMapping - Debug ]----------"
	@cd "OccupacyGridMapping" && "$(MAKE)" -f  "OccupacyGridMapping.mk"
clean:
	@echo "----------Cleaning project:[ OccupacyGridMapping - Debug ]----------"
	@cd "OccupacyGridMapping" && "$(MAKE)" -f  "OccupacyGridMapping.mk" clean
