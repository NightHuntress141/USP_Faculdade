/**
 * Esta classe representa um dos disparos ativos usado no jogo. Essa classe sempre deve ser
 * instanciada quando um disparo for feito por algum dos jogadores.
 */
public class Shot implements ISolid {
	private Player owner;
	private double cx, cy, size, vx, vy, speed;
	private boolean active;

	/**
		Construtor da classe Shot.

		@param player dono do disparo.
		@param cx coordenada x da posição inicial do disparo (centro do quadrado que a representa).
		@param cy coordenada y da posição inicial do disparo (centro do quadrado que a representa).
		@param size tamanho do quadrado que representa o disparo
		@param direction ângulo do disparo em graus
		@param speed velocidade da bola (em pixels por milissegundo).
	*/
	public Shot(Player player, double cx, double cy, double size, double direction, double speed){
		this.owner = player;
		this.cx = cx;
		this.cy = cy;
		this.size = size;
		this.speed = speed;
		active = true;

		vx = Math.cos(Math.toRadians(direction));
		vy = Math.sin(Math.toRadians(direction));
	}

	/**
		Método chamado sempre que o disparo precisa ser (re)desenhada.
	*/
	public void draw(){
		GameLib.setColor(owner.getColor());
		GameLib.fillRect(cx, cy, size, size);
	}

	/**
		Método chamado quando o estado (posição) do disparo precisa ser atualizado.
		
		@param delta quantidade de milissegundos que se passou entre o ciclo anterior de atualização do jogo e o atual.
	*/
	public void update(long delta) {
		if (active) {
			cx += delta * vx;
			cy += delta * vy;
		}
	} 

	/**
		Método chamado quando detecta-se uma colisão do disparo com um jogador.
	
		@param player o jogador que foi acertado.
	*/
	public void onPlayerCollision(Player player){
		active = false;
		player.die();
	} 

	/**
		Método chamado quando detecta-se uma colisão do disparo com alguma parede.
	*/
	public void onWallCollision(){
		active = false;
	} 

	/**
		Método que verifica se houve colisão ou não do disparo com uma parede.

		@param wall referência para uma instância de Wall contra a qual será verificada a( ocorrência de colisão da bola.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/
	public boolean checkCollision(Wall wall){
		if (!active) return false;
		boolean collision;

		if (Collision.checkCollision(this, wall)) collision = true;
		else collision = false;

		return collision;
	} 

	/**
		Método que verifica se houve colisão do disparo algum jogador.

		@param player referência para uma instância de Player contra o qual será verificada a ocorrência de colisão do disparo.
		@return um valor booleano que indica a ocorrência (true) ou não (false) de colisão.
	*/	
	public boolean checkCollision(Player player){
		if(player == this.owner) return false;

		if (!active) return false;
		boolean collision;

		if (Collision.checkCollision(this, player)) collision = true;

		else collision = false;

		return collision;
	} 

	/**
	 * Esse método diz se o disparo está ativo ainda ou não. Um disparo ativo ainda interage com os
	 * elementos do jogo.
	 */
	public boolean isActive() {
		return active; 
	} 

	/**
		Método que devolve a coordenada x do centro do quadrado que representa o disparo.
		@return o valor double da coordenada x.
	*/
	public double getCx(){
		return cx;
	} 

	/**
		Método que devolve a coordenada y do centro do quadrado que representa o disparo.
		@return o valor double da coordenada y.
	*/
	public double getCy(){
		return cy;
	} 

	/**
		Método que devolve a velocidade do disparo.
		@return o valor double da velocidade.

	*/
	public double getSpeed(){
		return speed;
	} 

	/** Obtém a largura do retângulo que representa o disparo. */
	public double getWidth() {
		return size;
	} 

	/** Obtém a altura do retângulo que representa o disparo. */
	public double getHeight() {
		return size;
	} 
 
	/**
	 * Obtém o dono desse disparo.
	 * @return o player que efetuou o disparo
	 */
	public Player getOwner() {
		return owner;
	} 
}
