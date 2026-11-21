
from fastapi import APIRouter

router = APIRouter()


@router.get("/health", tags=["Health"])
async def health_check():
    """Return the basic health status of the backend."""
    return {"status": "ok"}