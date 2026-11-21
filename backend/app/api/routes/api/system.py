from fastapi import APIRouter
from fastapi.responses import JSONResponse
from sqlalchemy import text
from sqlalchemy.exc import SQLAlchemyError

from app.database.database import engine


router = APIRouter(prefix="/api/v1/system", tags=["System"])


@router.get("/status")
def get_system_status():
    """Check backend and database availability."""
    try:
        with engine.connect() as connection:
            connection.execute(text("SELECT 1"))

        return {
            "backend": "ok",
            "database": "ok",
        }

    except SQLAlchemyError:
        return JSONResponse(
            status_code=503,
            content={
                "backend": "ok",
                "database": "unavailable",
            },
        )
    