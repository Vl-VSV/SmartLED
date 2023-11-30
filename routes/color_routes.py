from fastapi import APIRouter, HTTPException
from data_model import data

router = APIRouter()

# Colors
colors = {
    'red': 0,
    'orange': 22,
    'yellow': 43,
    'green': 85,
    'cyan': 128,
    'blue': 170,
    'violet': 192,
    'pink': 213,
}


@router.get('/set')
def set_color(color: str):
    """
    Decrease the speed level.

    **Modes**:
    - 1.2
    - 3.3
    - 3.4
    - 2.4
    - 2.5
    - 2.6

    **Returns**:
    - The new rainbow step level.

    **Raises**:
    - HTTPException: 400 Bad Request if the current mode or submode is not suitable for adjusting speed.
    """

    if color not in colors.keys():
        raise HTTPException(status_code=400, detail="Неизветный цвет")

    if data.mode == 1 and data.submode == 2:
        data.settings_0 = colors[color]
        return {'new_color': color, 'new_color_code': data.settings_0}

    elif data.mode == 2 and (4 <= data.submode <= 6):
        data.settings_1 = colors[color]
        return {'new_color': color, 'new_color_code': data.settings_1}

    elif data.mode == 3 and (3 <= data.submode <= 4):
        data.settings_0 = colors[color]
        return {'new_color': color, 'new_color_code': data.settings_0}

    else:
        raise HTTPException(status_code=400, detail="Нельзя изменить цвет в текущем режиме")
