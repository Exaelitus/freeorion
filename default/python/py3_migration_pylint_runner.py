from pylint import epylint as lint

from multiprocessing import cpu_count

# First path must be module in that directory, it is used as base by pylint
paths = [
    'common',
    'common/charting/charts.py',
    'auth/auth.py',
    'chat/chat.py',
    'handlers/inspect_freeOrionAIInterface.py',
    'handlers/inspect_universe_generation.py',
    'stub_generator',
    'tests/common/test_print_utils.py',
    'tests/AI/test_assertion_fails.py',
    'tests/AI/test_parse_ai_tag_grade.py',
    'tests/AI/test_read_only_dict.py',
    'tests/AI/test_savegame_manager.py',
    'tests/AI/character_test/character_strings_test.py',
    'tests/AI/character_test/character_test.py',
    'turn_events/turn_events.py',
    'universe_generation/empires.py',
    'universe_generation/fields.py',
    'universe_generation/galaxy.py',
    'universe_generation/monsters.py',
    'universe_generation/names.py',
    'universe_generation/natives.py',
    'universe_generation/options.py',
    'universe_generation/planets.py',
    'universe_generation/specials.py',
    'universe_generation/starnames.py',
    'universe_generation/starsystems.py',
    'universe_generation/universe_generator.py',
    'universe_generation/universe_statistics.py',
    'universe_generation/universe_tables.py',
    'universe_generation/util.py',
    'AI/AIDependencies.py',
    'AI/AIFleetMission.py',
    'AI/AIstate.py',
    'AI/aistate_interface.py',
    'AI/ColonisationAI.py',
    'AI/CombatRatingsAI.py',
    'AI/DiplomaticCorp.py',
    'AI/DynamicResearchAI.py',
    'AI/EnumsAI.py',
    'AI/EspionageAI.py',
    'AI/ExplorationAI.py',
    'AI/fleet_orders.py',
    'AI/FleetUtilsAI.py',
    'AI/FreeOrionAI.py',
    'AI/freeOrionAIInterface.pyi',
    'AI/InvasionAI.py',
    'AI/MilitaryAI.py',
    'AI/MoveUtilsAI.py',
    'AI/pathfinding.py',
    'AI/PlanetUtilsAI.py',
    'AI/PriorityAI.py',
    'AI/ProductionAI.py',
    'AI/ResearchAI.py',
    'AI/ResourcesAI.py',
    'AI/ShipDesignAI.py',
    'AI/target.py',
    'AI/TechsListsAI.py',
    'AI/turn_state.py',
    'AI/character',
    'AI/savegame_codec',
    'AI/freeorion_tools'
]

extra_args = ['--rcfile=py3_migration_pylint_config.ini', '-j %s' % cpu_count()]

command = " ".join(paths + extra_args)
lint.py_run(command)
